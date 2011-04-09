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


#include "schedule.h"


Schedule::Schedule(const QVector<QVariant> &data, Schedule* parent) {

	m_itemData = data;
	m_parentItem = parent;
}


Schedule::~Schedule() {
	
	qDeleteAll(m_childItems);	
}


Schedule* Schedule::child(int number) { 
	
	return m_childItems.value(number);    
}


int Schedule::childCount() const {
	
	return m_childItems.count();
}


int Schedule::childNumber() const {
	
	if (m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<Schedule*>(this));

	return 0;
}


int Schedule::columnCount() const {
	
	return m_itemData.count();
}


QVariant Schedule::data(int column) const {
	
	return m_itemData.value(column);
}


bool Schedule::insertChildren(int position, int count, int columns) {
	
	if (position < 0 || position > m_childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
		QVector<QVariant> data(columns);
		Schedule* item = new Schedule(data, this);
		m_childItems.insert(position, item);
	}
	
	return true;
}


Schedule* Schedule::parent() {
	
     return m_parentItem;
}


bool Schedule::removeChildren(int position, int count) {
	
	if (position < 0 || position + count > m_childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete m_childItems.takeAt(position);

	return true;
}


bool Schedule::removeColumns(int position, int columns) {
	
	if (position < 0 || position + columns > m_itemData.size())
		return false;

	for (int column = 0; column < columns; ++column)
		m_itemData.remove(position);

	foreach (Schedule* child, m_childItems)
		child->removeColumns(position, columns);

	return true;
}


bool Schedule::setData(int column, const QVariant &value) {
	
	if (column < 0 || column >= m_itemData.size())
		return false;

	m_itemData[column] = value;
	
	return true;
}
