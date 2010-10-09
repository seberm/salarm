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


#ifndef SCHEDULERMODEL_H
#define SCHEDULERMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class Schedule;


class SchedulerModel : public QAbstractItemModel {

Q_OBJECT

public:
	//! Constructor
	/*!
	  \param parent parent object
	*/
    //explicit SchedulerModel(QObject *parent = 0);
	SchedulerModel(const QStringList &headers, QObject *parent = 0); 
	
	//! Destructor
	~SchedulerModel();
	
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	//bool insertColumns(int position, int columns, const QModelIndex &parent);
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
	//bool removeColumns(int position, int columns, const QModelIndex &parent);
	
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;
	
	
private:
	Schedule* _rootItem;
	
	Schedule* getItem(const QModelIndex &index) const;
	
	
signals:

public slots:

};

#endif // SCHEDULERMODEL_H
