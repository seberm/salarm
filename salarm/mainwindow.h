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


//! It provides a main window of sAlarm
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
	
	//! When language is changed the window is retranslated
	void changeEvent(QEvent* e);
	
	//! Close event handler
	/*!
	  It is executed when trying to close main window.
	  \param event pointer to QCloseEvent
	*/
	void closeEvent(QCloseEvent* event);

	
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
	/*!
	  \sa writeSettings()
	*/
	void readSettings();
	
	//! Saves application and window settings	
	/*!
	  \sa readSettings()
	*/
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
	
	//! Pointer to current date and time label
	QLabel *m_lblCurrentDateTime;
	
	//! Pointer to application timer
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
	
	//! Opens a browser with project bugzilla
	void reportBug();
	
	//! Shows preferences dialog
	void openPreferences();
	
	//! Exports schedules
	/*!
	  It opens a save dialog and saves a dump file with schedules and their category, expiration, title and description.
	  \sa importSchedules()
	*/
	void exportSchedules();
	
	//! Imports schedules from file
	/*!
	  
	  \sa exportSchedules()
	*/
	void importSchedules();
	
	//! Shows the dialog that helps simplify add the schedule into schedules list
	/*!
	  \sa removeSchedule()
	*/
	void addSchedule();
	
	//! Removes a schedule from schedule list
	/*!
	  \sa addSchedule()
	*/
	void removeSchedule();
	
	//! Shows context menu on given point
	/*!
	  \param point
	*/
	void showContextMenu(const QPoint &point);
	
	//! Edits schedule on given index
	/*!
	  \param index of schedule which we want to edit
	*/
	void editSchedule(const QModelIndex &index);
	
	//! Overloaded edit-schedule function
	void editSchedule();
	
	/*!
	  \param int is the schedule database id
	*/
	void timeoutInformation(int);
	
	//! Updates pieces of information in status bar
	/*!
	  It is called whenever timer object emits timeout() signal
	*/
	void updateStatusBar();
	
	//! It's called whenever some key is pressed
	/*!
	  This slot is connected with KeyCatcher signal keyPressed(int).
	*/
	void keyPressed(int key);
	
};

#endif // MAINWINDOW_H
