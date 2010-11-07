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
#include <QMessageBox>

#include <QtSql>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	
    ui->setupUi(this);
	
	// Start the splash screen
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/splashs/sAlarmIcon"));
	splash->show();
	
	// The alignment of the splash notice text
	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	
	splash->showMessage(QObject::tr("Connecting the database ..."), topRight, Qt::white);
	m_db = new Database ("Schedules");
	
	if (m_db->dbConnect())
		qDebug() << "Successfuly connected - " << m_db->getConnectionName();
	else {
		qDebug() << "Error in connection - " << m_db->getConnectionName();
		QMessageBox::critical(this, tr("Database connection"), tr("Error in database connection..."));
	}
	
	
	splash->showMessage(QObject::tr("Setting up the main window ..."), topRight, Qt::white);
	readSettings();

	m_trayIcon = new QSystemTrayIcon(QIcon(":/icons/alarmIcon"), this);
	
	QMenu *trayMenu = new QMenu;
	trayMenu->addAction(ui->actionQuit);
	m_trayIcon->setContextMenu(trayMenu);
	m_trayIcon->setToolTip(qApp->applicationName().append(" - ").append(qApp->applicationVersion()));
	m_trayIcon->setVisible(true);
	
	m_scheduler = new Scheduler(this);
	m_scheduler->setContextMenuPolicy(Qt::CustomContextMenu);
	setCentralWidget(m_scheduler);
	
	// Label which shows the realtime
	m_lblCurrentDateTime = new QLabel;
	
	createStatusBar();
	
	// StatusBar is updated every 500ms (0.5 second)
	m_timer = new QTimer(this);
	m_timer->setInterval(500);
	connect (m_timer, SIGNAL(timeout()), this, SLOT(updateStatusBar()));
	m_timer->start();
	
createToolsBar();
	
	splash->showMessage(tr("Making object connections ..."), topRight, Qt::white);
	makeConnections();
	
	splash->finish(this);
	delete splash;
}


void MainWindow::makeConnections() const {
	
	connect (m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));
	
	connect (ui->actionPreferences, SIGNAL(triggered()), SLOT(openPreferences()));
	connect (ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect (ui->actionAboutThisApplication, SIGNAL(triggered()), this, SLOT(about()));
	connect (ui->actionReportBug, SIGNAL(triggered()), this, SLOT(reportBug()));
	connect (ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect (ui->actionEdit, SIGNAL(triggered()), this, SLOT(editSchedule()));
	connect (ui->actionNew, SIGNAL(triggered()), this, SLOT(addSchedule()));
	connect (ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeSchedule()));
	
	connect (m_scheduler, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
	
	connect (m_scheduler, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editSchedule(QModelIndex)));
	
	connect (m_scheduler, SIGNAL(scheduleTimeouted(int)), this, SLOT(timeoutInformation(int)));
}


MainWindow::~MainWindow() {
	
	writeSettings();
	
	delete m_db;
    delete ui;
}


void MainWindow::writeSettings() const {
	
	m_settings->beginGroup("Window");
		m_settings->setValue("Geometry", saveGeometry());
		m_settings->setValue("State", saveState());
	m_settings->endGroup();
}


void MainWindow::readSettings() {	
	
	// Load new settings
	if (!QFile::exists(CONF_DIR)) {
		
		QDir newDir;
		if (!newDir.mkdir(CONF_DIR)) {
			
			qDebug() << tr("Unable to create directory: %1").arg(CONF_DIR);
			return;
		}
	}
	
	m_settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, this);
	
	m_settings->beginGroup("Window");
		restoreGeometry(m_settings->value("Geometry", saveGeometry()).toByteArray());
		restoreState(m_settings->value("State", saveState()).toByteArray());
	m_settings->endGroup();
	
	
	m_settings->beginGroup("App");
		m_canClose = m_settings->value("CanClose", false).toBool();
	m_settings->endGroup();
}


void MainWindow::createStatusBar() {
	
	QLabel *lblVersion = new QLabel(tr("Version: ") + qApp->applicationVersion());
	lblVersion->setMinimumSize(lblVersion->sizeHint());
	
	m_lblCurrentDateTime->setAlignment(Qt::AlignRight);
	m_lblCurrentDateTime->setMinimumSize(m_lblCurrentDateTime->sizeHint());
	
	m_statusBar = new QStatusBar(this);
	
	m_statusBar->addWidget(lblVersion, 20);
	m_statusBar->addWidget(m_lblCurrentDateTime, 30);
	
	setStatusBar(m_statusBar);
}


void MainWindow::updateStatusBar() {
	
	m_lblCurrentDateTime->setText(QDateTime::currentDateTime().toString());
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
		if (m_canClose) {
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
	
	OptionsDialog *d = new OptionsDialog(m_settings, this);
	
	if (d->exec() == QDialog::Accepted) {
		
		// Reads new settings
		readSettings();
	}
}


void MainWindow::addSchedule() {
	
	ScheduleDialog *d = new ScheduleDialog(this);
	
	// We need to refresh the schedule list every time the schedules change
	connect (d, SIGNAL(changed()), m_scheduler, SLOT(refreshSchedules()));
	
	// Opens the ScheduleDialog
	d->exec();
}


void MainWindow::removeSchedule() {
	
	m_scheduler->removeSchedule();
}


void MainWindow::showContextMenu(const QPoint &p) {

	//ui->menuSchedule->popup(m_scheduler->header()->mapToGlobal(p));
	
	ui->menuSchedule->popup(m_scheduler->viewport()->mapToGlobal(p));
}


void MainWindow::editSchedule(const QModelIndex &i) {
	
	ScheduleDialog *d = new ScheduleDialog(i, this);
	connect (d, SIGNAL(changed()), m_scheduler, SLOT(refreshSchedules()));
	
	d->exec();
}


// Overloaded function
void MainWindow::editSchedule() {
	
	QModelIndex i(m_scheduler->currentIndex());
	editSchedule(i);
}


void MainWindow::timeoutInformation(int ID) {
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sqlData = "SELECT title, text" \
					  " FROM Schedule" \
					  " WHERE id = ?;";
	
	QSqlQuery queryData(sqlConnection);
	
	queryData.prepare(sqlData);
	queryData.addBindValue(ID);
	
	if (!queryData.exec())
		qDebug() << queryData.lastError();
	
	while (queryData.next()) {
		
		QString title = queryData.value(0).toString();
		QString text = queryData.value(1).toString();
	
		QString message = tr("Schedule %1 timeouted!<br><br><br>%2").arg(title).arg(text);
		QMessageBox::information(this, tr("Timeouted"), message);

		m_trayIcon->showMessage(tr("Timeouted"), tr("Schedule %1 just timeouted.").arg(title));
	}
	
}

