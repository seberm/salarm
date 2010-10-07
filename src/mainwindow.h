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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>

#include <QLabel>
#include <QTimer>
#include <QStatusBar>

#include "scheduler.h"
#include "database.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

	
protected:
	
	void changeEvent(QEvent* e);
	void closeEvent(QCloseEvent* e);

	
private:
	
	//! Creates the StatusBar on the MainWindow
	void createStatusBar();
	
	//! Creates the tools box
	void createToolsBar();
	
	//! Makes the connections between objects
	void makeConnections() const;
	
void readSettings();
void writeSettings() const;
	
	//! Opens a confirmation messageBox
	/*!
	  \return Returns true when is clicked on "Yes"
	*/
	bool okToContinue();
	
	
	//! The MainWindow variable
	Ui::MainWindow *ui;
	
	//! Indicates if the user can close the MainWindow
	bool _canClose;
	
	QSettings* _settings;	
	QSystemTrayIcon* _trayIcon;	
	QStatusBar* _statusBar;
	Scheduler* _scheduler;
	QLabel *_lblCurrentDateTime;
	QTimer *_timer;
	
	//! The database class pointer
	Database* _db;
			
	
private slots:
	
	//! Shows or hides the MainWindow
	void showHide (QSystemTrayIcon::ActivationReason);
	void about();
	void reportBug();
	void openPreferences();
	
	void updateStatusBar();
	
	//! Shows the dialog that helps simplify add the schedule into the SchedulesList
	void addSchedule();
	void removeSchedule();
	void showContextMenu(const QPoint &);
	
	void editSchedule(const QModelIndex &);
	void editSchedule();
	

};

#endif // MAINWINDOW_H
