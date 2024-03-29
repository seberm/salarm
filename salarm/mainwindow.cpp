/*
 * sAlarm - Scheduler
 * http://salarm.seberm.com
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


#include <QDir>
#include <QUrl>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDesktopServices>
#include <QtDebug>
#include <QSplashScreen>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "scheduledialog.h"
#include "timeoutdialog.h"
#include "xmlhandler.h"
#include "constants.h"
#include "scheduler.h"
#include "keycatcher.h"
#include "database.h"

#include "settings.h"
extern QSettings *g_settings;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	
    ui->setupUi(this);
	initSettings();

	// Start the splash screen
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/splashs/sAlarmIcon"));
	splash->show();
	
	// The alignment of the splash notice text
	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	
	splash->showMessage(tr("Setting up the main window ..."), topRight, Qt::white);
	readSettings();

	createTrayIcon();
	
	// Connect the database manager
	m_sqlDb = new Database("Schedules");
	
	if (m_sqlDb->connect())
		qDebug() << tr("Successfuly connected - %1").arg(m_sqlDb->connectionName());
	else qCritical() << tr("error in database connection - %1").arg(m_sqlDb->connectionName());
	
	
	m_scheduler = new Scheduler(m_sqlDb, this);
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
	
	createToolBar();
	
	// Set the key catcher widget
	m_keyCatcher = new KeyCatcher(this);
	m_scheduler->installEventFilter(m_keyCatcher);
	
	splash->showMessage(tr("Making object connections ..."), topRight, Qt::white);
	makeConnections();

	splash->finish(this);
	delete splash;
}


void MainWindow::makeConnections() const {
	
	connect (m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivation(QSystemTrayIcon::ActivationReason)));
	
	connect (ui->actionPreferences, SIGNAL(triggered()), SLOT(openPreferences()));
	connect (ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect (ui->actionAboutThisApplication, SIGNAL(triggered()), this, SLOT(about()));
	connect (ui->actionReportBug, SIGNAL(triggered()), this, SLOT(reportBug()));
	connect (ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect (ui->actionEdit, SIGNAL(triggered()), this, SLOT(editSchedule()));
	connect (ui->actionNew, SIGNAL(triggered()), this, SLOT(addSchedule()));
	connect (ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeSchedule()));
	connect (ui->actionShowHide, SIGNAL(triggered()), this, SLOT(showHide()));
	connect (ui->actionExportSchedules, SIGNAL(triggered()), this, SLOT(exportSchedules()));
	connect (ui->actionImportSchedules, SIGNAL(triggered()), this, SLOT(importSchedules()));
	
	connect (m_scheduler, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
	connect (m_scheduler, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editSchedule(QModelIndex)));
	connect (m_scheduler, SIGNAL(scheduleTimeouted(int)), this, SLOT(timeoutInformation(int)));
	
	connect (m_keyCatcher, SIGNAL(keyPressed(int)), this, SLOT(keyPressed(int)));
}


MainWindow::~MainWindow() {

	writeSettings();
	
	// Removes the settings variable from memory
	exitSettings();	
	
	delete m_sqlDb;
    delete ui;
}


void MainWindow::writeSettings() const {
	
	if (!g_settings) {
		
		qCritical() << tr("cannot load settings");
		return;
	}

	g_settings->beginGroup("Window");
		g_settings->setValue("Geometry", saveGeometry());
		g_settings->setValue("State", saveState());
	g_settings->endGroup();
}


void MainWindow::readSettings() {	
	
	// Load new settings
	if (!QFile::exists(CONF_DIR)) {
		
		QDir newDir;
		if (!newDir.mkdir(CONF_DIR)) {
			
			qWarning() << tr("unable to create directory: %1").arg(CONF_DIR);
			return;
		}
	}
	
	if (!g_settings) {
		
		qCritical() << "cannot load settings";
		return;
	}
	
	g_settings->beginGroup("Window");
		restoreGeometry(g_settings->value("Geometry", saveGeometry()).toByteArray());
		restoreState(g_settings->value("State", saveState()).toByteArray());
	g_settings->endGroup();
}


void MainWindow::createStatusBar() {
	
	QLabel *lblVersion = new QLabel(tr("Version: %1").arg(qApp->applicationVersion()));
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


void MainWindow::createToolBar() {
	
	m_toolBar = addToolBar(tr("Tool Bar"));
	m_toolBar->setObjectName("mainToolBar");
	
	// We add some main actions into the tool bar
	m_toolBar->addAction(ui->actionNew);
	m_toolBar->addAction(ui->actionEdit);
	m_toolBar->addAction(ui->actionRemove);
	m_toolBar->addSeparator();
	m_toolBar->addAction(ui->actionPreferences);
	m_toolBar->addAction(ui->actionExportSchedules);
	m_toolBar->addAction(ui->actionImportSchedules);
}


void MainWindow::createTrayIcon() {
	
	m_trayIcon = new QSystemTrayIcon(QIcon(":/icons/alarmIcon"), this);
	
	QMenu *trayMenu = new QMenu;
	
	trayMenu->addAction(ui->actionShowHide);
	trayMenu->addSeparator();
	trayMenu->addAction(ui->actionQuit);
	
	
	m_trayIcon->setContextMenu(trayMenu);
	m_trayIcon->setToolTip(qApp->applicationName().append(" - ").append(qApp->applicationVersion()));
	m_trayIcon->setVisible(true);
}


void MainWindow::keyPressed(int key) {
	
	switch (key) {
		
		case Qt::Key_Return:
		case Qt::Key_Enter:
			
			editSchedule();
			break;
			
		default:
			return;
			break;
	}
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


void MainWindow::closeEvent(QCloseEvent *event) {
	
	if (isVisible()) {
		
		if (g_settings->value("App/CanClose", false).toBool()) {
			event->accept();
			qApp->quit();
		} else {
			event->ignore();
			hide();
		}
	}
}


void MainWindow::trayActivation(QSystemTrayIcon::ActivationReason reason) {
	
	if (reason == QSystemTrayIcon::Trigger) {
		
		if (isVisible())
			hide();
		else show();
	}
}


void MainWindow::showHide() {
	
	if (isHidden())
		show();
	else hide();
}


void MainWindow::about() {
	
	QString message = tr("<h2>%2</h2>"\
							 "<i><b>Version:</b> %1</i><br>"\
							 "<b>Author:</b> Sabart Otto (Seberm)<br>"\
							 "<b>Contact:</b> <a href=mailto:seberm@gmail.com>seberm@gmail.com</a><br>"\
							 "<b>Homepage:</b> <a href=http://salarm.seberm.com>sAlarm.Seberm.com</a><br><br>"\
							 "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.").arg(qApp->applicationVersion(), qApp->applicationName());	
	
	QMessageBox::about(this, tr("About %1\n%2").arg(qApp->applicationName()), message.toAscii());
}


void MainWindow::reportBug() {
	
	// Opens page of the project
	QDesktopServices::openUrl(QUrl(qApp->property("projectBugzilla").toString(), QUrl::TolerantMode));
}


void MainWindow::openPreferences() {
	
	OptionsDialog *d = new OptionsDialog(this);
	d->exec();
}


void MainWindow::addSchedule() {
	
	ScheduleDialog *d = new ScheduleDialog(m_sqlDb, m_scheduler, this);
	
	// Opens the ScheduleDialog
	d->exec();
}


void MainWindow::removeSchedule() {
	
	m_scheduler->removeSchedule();
}


void MainWindow::showContextMenu(const QPoint &point) {
	
	// Popup context menu at given point
	ui->menuSchedule->popup(m_scheduler->viewport()->mapToGlobal(point));
}


void MainWindow::editSchedule(const QModelIndex &index) {
	
	// Check if model index is valid
	if (!index.isValid())
		return;
	
	// Check if there are schedules
	if (m_scheduler->model()->rowCount()) {
		
		// Shows a schedule dialog
		ScheduleDialog *d = new ScheduleDialog(m_sqlDb, m_scheduler, index, this);
		d->exec();
	}
}


void MainWindow::editSchedule() {
	
	QModelIndex i(m_scheduler->currentIndex());
	
	editSchedule(i);
}


void MainWindow::timeoutInformation(int id) {
	
	// We create timeout dialog with given schedule ID
	TimeoutDialog *d = new TimeoutDialog(id, this);
	
	// When postpone button is pressed
	connect(d, SIGNAL(postponed(int)), m_scheduler, SLOT(postpone(int)));
	connect(d, SIGNAL(confirmed(int)), m_scheduler, SLOT(markTimeouted(int)));
	
	// Popup dialog
	d->exec();
}


void MainWindow::importSchedules() {
	
//! \todo pozdeji umoznit vice souboru najednou a to asi ve vlaknech, aby aplikace nacitala automaticky xml a zaroven se program nezastavil a nestal po tu dobu necinnym
	QString filename = QFileDialog::getOpenFileName(this, tr("Open file to import"), QDir::homePath(), tr("XML Files (*.xml);;All files (*.*)"));
	
	if (filename.isEmpty())
		return;
	
	QFile file(filename);
	QXmlInputSource iSource(&file);
	QXmlSimpleReader reader;
	
	XmlHandler handler(m_scheduler);
	reader.setContentHandler(&handler);
	reader.setErrorHandler(&handler);
	
	if (!reader.parse(iSource))
		qWarning() << tr("unable to parse xml file %1").arg(file.fileName());
	
}


void MainWindow::exportSchedules() {
	
	if (m_scheduler->model()->rowCount() <= 0) {
	
		QMessageBox::warning(this, tr("No schedules"), tr("There are no schedules to export"));
		return;
	}
	
	QString filename = QFileDialog::getSaveFileName(this, tr("Save exported file to"), QDir::homePath(), tr("XML Files (*.xml);;All files (*.*)"));
	
	QFile f(filename);
	m_scheduler->generateXmlToFile(&f);
}
