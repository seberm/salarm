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


#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H


#include <QDialog>
#include <QDateTime>
#include <QModelIndex>


namespace Ui {
	
    class ScheduleDialog;
}

class Database;
class Scheduler;

//! ScheduleDialog is dialog for inserting or editing of schedules
class ScheduleDialog : public QDialog {
    
	Q_OBJECT
	
	Q_ENUMS(ScheduleActions)
		
			
public:
	
	//! Constructor
	/*!
	  \param parent pointer to parent widget
	*/
	explicit ScheduleDialog(Database *sqlDb, Scheduler *scheduler, QWidget *parent = 0);
	
	//! Overloaded contructor
	/*!
	  This constructor is called when the schedule is edited.
	  \param scheduler pointer to Scheduler object
	  \param sqlDb pointer to database instance
	  \param parent pointer to parent widget
	*/
	ScheduleDialog(Database *sqlDb, Scheduler *scheduler, const QModelIndex &, QWidget *parent = 0);
	
	//! Destructor
    ~ScheduleDialog();
	
	//! Enum which indicates editation or insertion of schedule
	enum ScheduleActions { Add, Edit };

	
protected:
	
	//! When the language is changed the window is simply retranslated
	/*!
	  \param event contains more specific pieces of information about event
	*/
    void changeEvent(QEvent *event);

	
private:
	
	//! Initializes combo boxes, date and time
	void initialize();
	
	//! Add or Edit the new schedule into the list and DB
	void doSchedule();
	
	//! Makes the connections between objects
	void makeConnections();
	
	//! The Dialog pointer
	Ui::ScheduleDialog *ui;
	
	//! Enum valiable
	/*!
	  \sa ScheduleActions
	*/
	ScheduleDialog::ScheduleActions dialogAction;
	
	//! Represents the ID of schedule which is modified; if the schedule is inserted, the value is 0
	int m_scheduleID;
	
	//! Pointer to Database object
	Database *m_sqlDb;
	
	//! Pointer to Scheduler object
	Scheduler *m_scheduler;
	
	
private slots:
	
	//! The schedule dialog is accepted
	void scheduleAccepted();
	
	//! Shows the add category input dialog
	void addCategory();
	
	//! Removes current category from combo box
	void removeCategory();
	
};

#endif // SCHEDULEDIALOG_H
