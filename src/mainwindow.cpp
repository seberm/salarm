/*
 * sAlarm - Scheduler
 * http://seberm.homelinux.org/project/salarm
 *
 * Copyright (C) 2009-2010 Otto Sabart <seberm[at]gmail[dot]com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "scheduledialog.h"

#include "constants.h"

#include <QDir>
#include <QUrl>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QtDebug>
#include <QSplashScreen>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
	
	// Start the splash screen
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/splashs/tuxSplash"));
	splash->show();
	
	// The alignment of the splash notice text
	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	
	splash->showMessage(QObject::tr("Connecting the database ..."), topRight, Qt::white);
	_db = new Database ("Schedules");
	
	if (_db->dbConnect())
		qDebug() << "Successfuly connected - " << _db->getConnectionName();
	else {
		qDebug() << "Error in connection - " << _db->getConnectionName();
		QMessageBox::critical(this, tr("Database connection"), tr("Error in database connection..."));
	}
	
	splash->showMessage(QObject::tr("Setting up the main window ..."), topRight, Qt::white);
	readSettings();

	_trayIcon = new QSystemTrayIcon(QIcon(":/icons/alarmIcon"), this);
	
	QMenu *trayMenu = new QMenu;
	trayMenu->addAction(ui->actionQuit);
	_trayIcon->setContextMenu(trayMenu);
	_trayIcon->setToolTip(qApp->applicationName().append(" - ").append(qApp->applicationVersion()));
	_trayIcon->setVisible(true);
	
	_scheduler = new Scheduler(this);
	_scheduler->setContextMenuPolicy(Qt::CustomContextMenu);
	setCentralWidget(_scheduler);
	
	// Label which shows the realtime
	_lblCurrentDateTime = new QLabel;
	
	createStatusBar();
	
	// StatusBar is updated every 500ms (0.5 second)
	_timer = new QTimer(this);
	_timer->setInterval(1000);
	connect (_timer, SIGNAL(timeout()), this, SLOT(updateStatusBar()));
	_timer->start();
	
createToolsBar();
	
	splash->showMessage(tr("Making object connections ..."), topRight, Qt::white);
	makeConnections();
	
	splash->finish(this);
	delete splash;
}


void MainWindow::makeConnections() const {
	
	connect (_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));
	
	connect (ui->actionPreferences, SIGNAL(triggered()), SLOT(openPreferences()));
	connect (ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect (ui->actionAboutThisApplication, SIGNAL(triggered()), this, SLOT(about()));
	connect (ui->actionReportBug, SIGNAL(triggered()), this, SLOT(reportBug()));
	connect (ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect (ui->actionEdit, SIGNAL(triggered()), this, SLOT(editSchedule()));
	connect (ui->actionNew, SIGNAL(triggered()), this, SLOT(addSchedule()));
	connect (ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeSchedule()));
	
	connect (_scheduler, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
	
	connect (_scheduler, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editSchedule(QModelIndex)));
}


MainWindow::~MainWindow() {
	
	writeSettings();
	
	delete _db;
    delete ui;
}


void MainWindow::writeSettings() const {
	
	_settings->beginGroup("Window");
		_settings->setValue("Geometry", saveGeometry());
		_settings->setValue("State", saveState());
	_settings->endGroup();
}


void MainWindow::readSettings() {	
	
	// Load new settings
	_settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, this);
	
	_settings->beginGroup("Window");
		restoreGeometry(_settings->value("Geometry", saveGeometry()).toByteArray());
		restoreState(_settings->value("State", saveState()).toByteArray());
	_settings->endGroup();
	
	
	_settings->beginGroup("App");
		_canClose = _settings->value("CanClose", false).toBool();
	_settings->endGroup();
}


void MainWindow::createStatusBar() {
	
	QLabel *lblVersion = new QLabel(tr("Version: ") + qApp->applicationVersion());
	lblVersion->setMinimumSize(lblVersion->sizeHint());
	
	_lblCurrentDateTime->setAlignment(Qt::AlignRight);
	_lblCurrentDateTime->setMinimumSize(_lblCurrentDateTime->sizeHint());
	
	_statusBar = new QStatusBar(this);
	
	_statusBar->addWidget(lblVersion, 20);
	_statusBar->addWidget(_lblCurrentDateTime, 30);
	
	setStatusBar(_statusBar);
}


void MainWindow::updateStatusBar() {
	
	_lblCurrentDateTime->setText(QDateTime::currentDateTime().toString());
}


void MainWindow::createToolsBar() {
	
}


bool MainWindow::okToContinue() {
	
//! \todo For now it's unnecessary. Afterwards complete the message.
	
	int auxVar = QMessageBox::warning(this, tr("sAlarm warning"),
									  tr("Do you want to save your changes?"),
									  QMessageBox::Yes | QMessageBox::Default,
									  QMessageBox::No,
									  QMessageBox::Cancel | QMessageBox::Escape);
	
	switch (auxVar) {
		case QMessageBox::Yes: {
			return true;
			break;
		}
		
		default:
			return false;
			break;
	}
}


void MainWindow::changeEvent(QEvent *e) {
	
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::closeEvent(QCloseEvent *e) {
	
	if (isVisible()) {
		if (_canClose) {
			e->accept();
			close();
		} else {
			e->ignore();
			hide();
		}
	}
}


void MainWindow::showHide(QSystemTrayIcon::ActivationReason reason) {
	
	if (reason == QSystemTrayIcon::Trigger) {
		if (this->isVisible())
			hide();
		else show();
	}
}


void MainWindow::about() {
	
	QString message = QString(tr("<h2>%2</h2>"\
							 "<i><b>Version:</b> %1</i><br>"\
							 "<b>Author:</b> Sabart Otto (Seberm)<br>"\
							 "<b>Contact:</b> <a href=mailto:seberm@gmail.com>seberm@gmail.com</a><br>"\
							 "<b>Homepage:</b> <a href=http://www.seberm.homelinux.org/project/salarm>seberm.homelinux.org</a><br><br>"\
							 "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.")).arg(QString(qApp->applicationVersion()), QString(qApp->applicationName()));	
	
	QMessageBox::about(this, tr("About ").append(qApp->applicationName()), message.toAscii());
}


void MainWindow::reportBug() {
	
	// Opens page of the project
	QDesktopServices::openUrl(QUrl("http://www.seberm.homelinux.org/project/salarm", QUrl::TolerantMode));
}


void MainWindow::openPreferences() {
	
	OptionsDialog *d = new OptionsDialog(_settings, this);
	//connect (d, SIGNAL(canCloseChanged()), this, SLOT(readSettings()));
			
	//connect (d, SIGNAL(accepted()), this, );
	d->exec();
}


void MainWindow::addSchedule() {
	
	ScheduleDialog *d = new ScheduleDialog(this);
	
	// We need to refresh the schedule list every time the schedules change
	connect (d, SIGNAL(changed()), _scheduler, SLOT(refreshSchedules()));
	
	// Opens the ScheduleDialog
	d->exec();
}


void MainWindow::removeSchedule() {
	
	_scheduler->removeSchedule();
}


void MainWindow::showContextMenu(const QPoint &p) {

	//ui->menuSchedule->popup(_scheduler->header()->mapToGlobal(p));
	
	ui->menuSchedule->popup(_scheduler->viewport()->mapToGlobal(p));
}


void MainWindow::editSchedule(const QModelIndex &i) {
	
	ScheduleDialog *d = new ScheduleDialog(i, this);
	connect (d, SIGNAL(changed()), _scheduler, SLOT(refreshSchedules()));
	
	d->exec();
}


// Overloaded function
void MainWindow::editSchedule() {
	
	QModelIndex i(_scheduler->currentIndex());
	editSchedule(i);
}

