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


#include "schedulerproxymodel.h"
#include "scheduler.h"


SchedulerProxyModel::SchedulerProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
	
	setFilterRole(Qt::EditRole);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
	setDynamicSortFilter(true);
}


bool SchedulerProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {

	extern const int columnCount;
	for (int col = 0; col < columnCount; col++) {
		
		QModelIndex index = sourceModel()->index(sourceRow, col, sourceParent);
		
		if (sourceModel()->data(index).toString().contains(filterRegExp()))
			return true;
		
	}
	
	return false;
}
