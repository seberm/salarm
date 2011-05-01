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


#include <QtGui>

#include "schedulermodel.h"
#include "schedule.h"


SchedulerModel::SchedulerModel(const QStringList &headers, QObject *parent) : QAbstractItemModel(parent) {
	
	QVector<QVariant> rootData;
	
	foreach (QString header, headers)
		rootData << header;
	
	m_rootItem = new Schedule(rootData);
}


SchedulerModel::~SchedulerModel() {
	
	delete m_rootItem;
}


QVariant SchedulerModel::data(const QModelIndex &index, int role) const {
	
	if (!index.isValid())
		return QVariant();
	
	if (role != Qt::DisplayRole && role != Qt::EditRole)	
		return QVariant();
	
	
	Schedule* item = getItem(index);
	
	return item->data(index.column());
}


QVariant SchedulerModel::headerData(int section, Qt::Orientation orientation, int role) const {
	
	if (role != Qt::DisplayRole)
		return QVariant();
   
	if (orientation == Qt::Horizontal) {
		/*switch (section) {
			case 0:
				return "DBID";
				
			case 1:
				return tr("Title");
   
			case 2:
				return tr("Text");
				
			case 3:
				return tr("Expiration");
   
			default:
				return QVariant();
			}
			*/
		return m_rootItem->data(section);
	}
	
	return QVariant();
}


bool SchedulerModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
	
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;
	
	bool result = m_rootItem->setData(section, value);
	
	if (result)
		emit headerDataChanged(orientation, section, section);
		
	return result;	
}


bool SchedulerModel::insertRows(int position, int rows, const QModelIndex &parent) {
	
	Schedule* parentItem = getItem(parent);
	bool success/* = false*/;
	
	beginInsertRows(parent, position, position + rows - 1);    
	success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
    endInsertRows();
     
	return success;
}


bool SchedulerModel::removeRows(int position, int rows, const QModelIndex &parent) {
	
	Schedule* parentItem = getItem(parent);
	bool success = true;	
    
	beginRemoveRows(parent, position, position + rows - 1);    
	success = parentItem->removeChildren(position, rows);
    endRemoveRows();
	
    return success;
}


bool SchedulerModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	
	if (!index.isValid())
		return false;
	
	if (role == Qt::DisplayRole) {
		Schedule* item = getItem(index);
		bool result = item->setData(index.column(), value);
		
		if (result)
			emit dataChanged(index, index);

        return result;
    }

    return false;
}


Qt::ItemFlags SchedulerModel::flags(const QModelIndex &index) const {
	
    if (!index.isValid())
        return Qt::ItemIsEnabled;

	//! \todo upravit return!
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;    
}


int SchedulerModel::columnCount(const QModelIndex &/*parent*/) const {
	
	return m_rootItem->columnCount();
}


int SchedulerModel::rowCount(const QModelIndex &parent) const {
	
	Schedule* parentItem = getItem(parent);

	return parentItem->childCount();
}


QModelIndex SchedulerModel::parent(const QModelIndex &index) const {
	
	if (!index.isValid())
		return QModelIndex();
	
	Schedule* childItem = getItem(index);
	Schedule* parentItem = childItem->parent();
	
	if (parentItem == m_rootItem)
		return QModelIndex();	

	
	return createIndex(parentItem->childNumber(), 0, parentItem);	
}


QModelIndex SchedulerModel::index(int row, int column, const QModelIndex &parent) const {
	
	if (parent.isValid() && parent.column() != 0)
			 return QModelIndex();
	
	Schedule* parentItem = getItem(parent);
	Schedule* childItem = parentItem->child(row);
	
	if (childItem)
		return createIndex(row, column, childItem);
	
	return QModelIndex();
}


Schedule* SchedulerModel::getItem(const QModelIndex &index) const {
	
	if (index.isValid()) {
		Schedule* item = static_cast<Schedule*>(index.internalPointer());
		
		if (item)
			return item;
	}
	
	return m_rootItem;
}
