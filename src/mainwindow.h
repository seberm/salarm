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


#include "scheduler.h"
#include "database.h"
#include "keycatcher.h"

#include <QMainWindow>
#include <QSystemTrayIcon>

#include <QLabel>
#include <QTimer>
#include <QStatusBar>
#include <QToolBar>


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
	void createToolBar();
	
	//! Creates the tray icon
	void createTrayIcon();
	
	//! Makes the connections between objects
	void makeConnections() const;

	//! Reads the main application settings
	void readSettings();
	
	//! Saves application and window settings	
	void writeSettings() const;

	
	//! Opens a confirmation messageBox
	/*!
	  \return Returns true when is clicked on "Yes"
	*/
	bool okToContinue();
	
	
	//! The MainWindow pointer
	Ui::MainWindow *ui;
	
	//! Indicates if the user can close the MainWindow
	bool m_canClose;
	
	QSystemTrayIcon *m_trayIcon;	
	QStatusBar *m_statusBar;
	QToolBar *m_toolBar;
	Scheduler *m_scheduler;
	KeyCatcher *m_keyCatcher;
	QLabel *m_lblCurrentDateTime;
	QTimer *m_timer;
	
	//! The database class pointer
	Database* m_db;
			
	
private slots:
	
	//! Shows or hides the MainWindow
	void showHide();
	
	//! Is called when tray icon is triggered
	void trayActivation(QSystemTrayIcon::ActivationReason);
	void about();
	void reportBug();
	void openPreferences();
	
	void updateStatusBar();
	
	//! Shows the dialog that helps simplify add the schedule into the SchedulesList
	void addSchedule();
	void removeSchedule();
	void showContextMenu(const QPoint &);
	
	void editSchedule(const QModelIndex &);
	
	//! Overloaded edit-schedule function
	void editSchedule();
	void keyPressed(int key);
	
	/*!
	  \param int is the schedule database id
	*/
	void timeoutInformation(int);
};

#endif // MAINWINDOW_H
