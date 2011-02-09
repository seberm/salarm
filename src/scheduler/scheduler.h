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


#ifndef SCHEDULER_H
#define SCHEDULER_H


#include <QTreeView>
#include <QDateTime>
#include <QTimer>
#include <QList>
#include <QSqlDatabase>


struct Column {
	
	int columnID;
	QString columnName;
};

class SchedulerModel;
class SchedulerProxyModel;
class ScheduleDelegate;
class Database;


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
			
	//! Removes schedule
	/*!
	  \param i pointer to QTreeWidgetItem class
	*/
	void removeSchedule();
	
	//! Makes the connections between objects
	void makeConnections();
	
	
public slots:
	
	//! Updates a list of schedules
	void refreshSchedules();
	
	//! Tells which schedules are timeouted
	void checkSchedules();
	
	void postpone(int id);
	
	void markTimeouted(int id);

signals:
	
	//! This signal is emitted when the schedule timeouted
	/*!
	  \param int schedule database ID
	*/
	void scheduleTimeouted (int);
	
	
private:

	SchedulerModel *m_model;
	SchedulerProxyModel *m_proxyModel;
	ScheduleDelegate *m_itemDelegate;
	
	QTimer *m_scheduleTimer;
	Database *m_sqlDb;
	
	//! Keeps the pairs of untimeouted schedules (<Database ID of schedule, Expiration datetime>)
	QList<QPair<int, QDateTime> > m_schedules;
};

#endif // SCHEDULER_H
