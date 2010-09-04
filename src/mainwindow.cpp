/*
 * sAlarm - Scheduler
 * http://seberm.homelinux.org/salarm
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

#include "constants.h"

#include <QDir>
#include <QUrl>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QtDebug>
#include <QSplashScreen>

#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
	
	// Start the splash screen
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/splashs/tuxSplash"));
	splash->show();
	
	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QObject::tr("Setting up the main window ..."), topRight, Qt::white);
	
	readSettings();
	restoreGeometry(_settings->value("Window/Geometry", this->saveGeometry()).toByteArray());
	restoreState(_settings->value("Window/State", saveState()).toByteArray());
	
	ui->dateTimeEditEndDateTime->setDateTime(QDateTime::currentDateTime());

	_trayIcon = new QSystemTrayIcon(QIcon(":/icons/alarmIcon"), this);
	QMenu *trayMenu = new QMenu;
	trayMenu->addAction(ui->actionQuit);
	_trayIcon->setContextMenu(trayMenu);
	_trayIcon->setToolTip(qApp->applicationName().append(" - ").append(qApp->applicationVersion()));
	_trayIcon->setVisible(true);
	
	createStatusBar();
	
	_timer = new Timer;
	_showTimeTimer = new QTimer(this);
	
	QStringList columnLabels;
	columnLabels << "DBID" 
                                 << tr("Title")
				 << tr("Text")
				 << tr("Date");
					
	ui->scheduler->setHeaderLabels(columnLabels);
        // Hide the first column that holds DBID
        ui->scheduler->setColumnHidden(0,true);
	
	splash->showMessage(tr("Making object connections ..."), topRight, Qt::white);
	makeConnections();
	
	splash->finish(this);
	delete splash;
}


void MainWindow::addSchedule() {
	ui->scheduler->addSchedule(ui->titleLineEdit->text(), ui->plainTextEditSchedule->toPlainText(), ui->dateTimeEditEndDateTime->dateTime());
}


void MainWindow::removeSchedule() {
	QList<QTreeWidgetItem *> items;
	
	items = ui->scheduler->selectedItems();
	
	for (int i = 0; i < items.count(); i++) {
		ui->scheduler->removeSchedule(items.at(i));	
	}
}


void MainWindow::makeConnections() {
	
	connect (_showTimeTimer, SIGNAL(timeout()), this, SLOT(printLCDTime()));
	
	connect (_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));
	
	connect (ui->actionPreferences, SIGNAL(triggered()), SLOT(openPreferences()));
	connect (ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect (ui->actionAboutThisApplication, SIGNAL(triggered()), this, SLOT(about()));
	connect (ui->actionReportBug, SIGNAL(triggered()), this, SLOT(reportBug()));
	connect (ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	connect (ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(addSchedule()));
	connect (ui->pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeSchedule()));
}


MainWindow::~MainWindow() {
	
	writeSettings();
	
	delete _timer;
    delete ui;
}


void MainWindow::writeSettings() {
	
	_settings->beginGroup("Window");
		_settings->setValue("Geometry", geometry());
		_settings->setValue("State", saveState());
	_settings->endGroup();
	
	_settings->beginGroup("App");
		_settings->setValue("CanClose", _canClose);
	_settings->endGroup();
}


void MainWindow::readSettings() {	
	
	// Load new settings
	_settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, this);
	
	_settings->beginGroup("App");
		_canClose = _settings->value("CanClose", false).toBool();
	_settings->endGroup();
	
	_settings->beginGroup("Window");
		QRect rect = _settings->value("Geometry", QRect(200, 200, 370, 450)).toRect();
	_settings->endGroup();
	
	move(rect.topLeft());
	resize(rect.size());
	
}


void MainWindow::createStatusBar() {
	
	QLabel *lblVersion = new QLabel(tr("Version: ") + qApp->applicationVersion());
	lblVersion->setAlignment(Qt::AlignRight);
	lblVersion->setMinimumSize(lblVersion->sizeHint());
	
	_statusBar = new QStatusBar(this);
	
	_statusBar->addWidget(lblVersion, 1);
	
	setStatusBar(_statusBar);
	
	updateStatusBar();
}


void MainWindow::updateStatusBar() {
	
	//! \todo Finish an updating of the statusBar
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
							 "<b>Contact:</b> seberm@gmail.com<br>"\
							 "<b>Homepage:</b> www.seberm.homelinux.org<br><br>"\
							 "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.")).arg(QString(qApp->applicationVersion()), QString(qApp->applicationName()));	
	
	QMessageBox::about(this, tr("About ").append(qApp->applicationName()), message.toAscii());
}


void MainWindow::reportBug() {
	
	// Opens page of the project
	QDesktopServices::openUrl(QUrl("http://www.seberm.homelinux.org/salarm", QUrl::TolerantMode));
}


void MainWindow::openPreferences() {
	
	OptionsDialog *d = new OptionsDialog(_settings, this);
	connect (d, SIGNAL(canCloseChanged()), this, SLOT(readSettings()));
			
	//connect (d, SIGNAL(accepted()), this, );
	d->exec();
}



//SLOT
void MainWindow::timeouted() {
	
	_timer->stopApp();
	_showTimeTimer->stop();
	
	_trayIcon->showMessage(tr("Timeouted"), tr("The timer has timeouted!"));
	ui->labelTimerInfo->setText(tr("Ended!"));
	ui->pushButtonStop->setDisabled(true);
	ui->pushButtonStart->setEnabled(true);
	ui->groupBoxTimer->setEnabled(true);
}


void MainWindow::on_pushButtonStart_clicked() {
	
	ui->pushButtonStart->setDisabled(true);
	ui->pushButtonStop->setEnabled(true);
	ui->groupBoxTimer->setDisabled(true);
	ui->labelTimerInfo->setText(tr("Timer started"));
	
	_showTimeTimer->start(1000);
	_timer->setTime(ui->spinBoxSeconds->value(), ui->spinBoxMinutes->value(), ui->spinBoxHours->value());
	
	connect (_timer, SIGNAL(timeout()), this, SLOT(timeouted()));
	_timer->startApp();
	
	ui->lcdNumber->display(_timer->interval() / 1000);
}


void MainWindow::on_pushButtonStop_clicked() {
	
	timeouted();
}


//SLOT
void MainWindow::printLCDTime() {
	
	ui->lcdNumber->display(ui->lcdNumber->intValue() - 1);
}
