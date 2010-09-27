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


#include "schedule.h"

Schedule::Schedule(const QVector<QVariant> &data, Schedule* parent) {

	_itemData = data;
	_parentItem = parent;
}


Schedule::~Schedule() {
	
	qDeleteAll(_childItems);	
}


Schedule* Schedule::child(int number) { 
	
	return _childItems.value(number);    
}


int Schedule::childCount() const {
	
	return _childItems.count();
}


int Schedule::childNumber() const {
	
	if (_parentItem)
		return _parentItem->_childItems.indexOf(const_cast<Schedule*>(this));

	return 0;
}


int Schedule::columnCount() const {
	
	return _itemData.count();
}


QVariant Schedule::data(int column) const {
	
	return _itemData.value(column);
}


bool Schedule::insertChildren(int position, int count, int columns) {
	
	if (position < 0 || position > _childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
		QVector<QVariant> data(columns);
		Schedule* item = new Schedule(data, this);
		_childItems.insert(position, item);
	}
	
	return true;
}


Schedule* Schedule::parent() {
	
     return _parentItem;
}


bool Schedule::removeChildren(int position, int count) {
	
	if (position < 0 || position + count > _childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete _childItems.takeAt(position);

	return true;
}


bool Schedule::removeColumns(int position, int columns) {
	
	if (position < 0 || position + columns > _itemData.size())
		return false;

	for (int column = 0; column < columns; ++column)
		_itemData.remove(position);

	foreach (Schedule* child, _childItems)
		child->removeColumns(position, columns);

	return true;
}


bool Schedule::setData(int column, const QVariant &value) {
	
	if (column < 0 || column >= _itemData.size())
		return false;

	_itemData[column] = value;
	
	return true;
}
