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


#ifndef SCHEDULER_H
#define SCHEDULER_H


#include <QTreeView>
#include <QDateTime>
#include <QTimer>
#include <QList>
#include <QFile>
#include <QSqlDatabase>


struct Column {
	
	int columnID;
	QString columnName;
};

class SchedulerModel;
class SchedulerProxyModel;
class ScheduleDelegate;
class Schedule;
class Database;

//! Provides QTreeWiew component with some more functions
class Scheduler : public QTreeView {
	
	Q_OBJECT

public:
	
	//! Constructor
	/*!
	  \param parent pointer to parent object
	*/
    explicit Scheduler(Database *sqlDb, QWidget *parent = 0);
	
	//! Destructor
	~Scheduler();
			
	//! Removes schedule at current model index
	/*!
	  \sa addSchedule()
	*/
	void removeSchedule();
	
	//! Adds a new schedule into Scheduler
	/*!
	  \param title title of the schedule
	  \param text description text
	  \param expiration indicates when schedule expire
	  \param categoryID schedule category database ID
	  \sa removeSchedule()
	*/
	void addSchedule(const QString &title, const QString &text, const QDateTime &expiration, int categoryID = 0);
	
	//! \todo It's not implemented yet
	void addSchedule(Schedule *s);
	
	//! Edits schedule
	/*!
	  \param id ID of schedule which we want to edit
	  \param title title of schedule
	  \param text schedule description text
	  \param expiration new date and time of schedule expiration
	  \param categoryID schedule category ID
	*/
	void editSchedule(int id, const QString &title, const QString &text, const QDateTime &expiration, int categoryID = 0);
	
	//! Makes connections between objects
	void makeConnections();
	
	//! Generates XML file with schedules to given file
	/*!
	  \param file file for export
	*/
	void generateXmlToFile(QFile *file);
	
	//! Updates list of schedules
	void refreshSchedules();
	
	
public slots:
	
	//! Checks schedules
	/*!
	  If some schedule timeouted it emites signal scheduleTimeouted(x) where "x" is schedule ID.
	*/
	void checkSchedules();
	
	//! Postpones schedule with given ID
	/*!
	  Postpone interval can be set in preferences.
	  \param id schedule ID
	*/
	void postpone(int id);
	
	//! Marks schedule with given ID timeouted
	/*!
	  \param id schedule ID
	*/
	void markTimeouted(int id);

signals:
	
	//! This signal is emitted when the schedule timeouted
	/*!
	  \param int schedule database ID
	*/
	void scheduleTimeouted (int);
	
	
private:

	//! Pointer to item model
	SchedulerModel *m_model;
	
	//! Pointer to item proxy model
	SchedulerProxyModel *m_proxyModel;
	
	//! Pointer to item model delegate
	ScheduleDelegate *m_itemDelegate;
	
	//! Pointer to timer
	QTimer *m_scheduleTimer;
	
	//! Pointer to database instance
	Database *m_sqlDb;
	
	//! Keeps the pairs of untimeouted schedules (<Database ID of schedule, Expiration datetime>)
	QList<QPair<int, QDateTime> > m_schedules;
};

#endif // SCHEDULER_H
