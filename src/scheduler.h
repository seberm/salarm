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


#include "database.h"

#include <QTreeWidget>
#include <QDateEdit>


class Scheduler : public QTreeView {
	
Q_OBJECT

public:
	//! Constructor
	/*!
	  \param parent pointer to parent object
	*/
    explicit Scheduler(QWidget *parent = 0);
	
	//! Adds a new schedule into the list and DB
	/*!
	  \param title the title of the schedule
	  \param text the schedule's text
	  \param expiration tells when the schedule expirate
	*/
	//void addSchedule(const QString &title, const QString &text, const QDateTime &expiration);
			
	//! Removes schedule
	/*!
	  \param i pointer to QTreeWidgetItem class
	*/
	//void removeSchedule(QTreeWidgetItem *i);
	
	
public slots:	
	//! Updates a list of schedules
	//void refreshSchedules();
	
	
private:
	//! The database class pointer
	//Database *_db;

};

#endif // SCHEDULER_H
