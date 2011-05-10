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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QLabel>
#include <QTimer>
#include <QStatusBar>
#include <QToolBar>
#include <QModelIndex>


class Scheduler;
class KeyCatcher;
class Database;

namespace Ui {	
    class MainWindow;
}


class MainWindow : public QMainWindow {
	
    Q_OBJECT

public:
	
	//! Constructor
	/*!
	  Constructs the mainwidnow.
	  \param parent pointer to parent object
	*/
	explicit MainWindow(QWidget* parent = 0);
	
	//! Destructor
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
	
	
	//! Pointer to main window's UI (it's generated from mainwindow.ui)
	Ui::MainWindow *ui;
	
	//! Indicates if the user can close the MainWindow by clicking on close
	bool m_canClose;
	
	//! Pointer to application's tray icon
	QSystemTrayIcon *m_trayIcon;
	
	//! Pointer to status bar
	QStatusBar *m_statusBar;
	
	//! Pointer to toolbar
	QToolBar *m_toolBar;
	
	QLabel *m_lblCurrentDateTime;
	QTimer *m_timer;
	
	//! Pointer to KeyCatcher
	KeyCatcher *m_keyCatcher;
	
	//! Pointer to Scheduler
	Scheduler *m_scheduler;
	
	//! The database class pointer
	Database *m_sqlDb;
			
	
private slots:
	
	//! Shows or hides the MainWindow
	void showHide();
	
	//! Is called when tray icon is triggered
	void trayActivation(QSystemTrayIcon::ActivationReason);
	
	//! Shows an about dialog
	void about();
	
	void reportBug();
	void openPreferences();
	void exportSchedules();
	void importSchedules();
	
	//! Shows the dialog that helps simplify add the schedule into the SchedulesList
	void addSchedule();
	void removeSchedule();
	void showContextMenu(const QPoint &);
	
	void editSchedule(const QModelIndex &);
	
	//! Overloaded edit-schedule function
	void editSchedule();
	
	/*!
	  \param int is the schedule database id
	*/
	void timeoutInformation(int);
	
	void updateStatusBar();
	void keyPressed(int key);
	
};

#endif // MAINWINDOW_H
