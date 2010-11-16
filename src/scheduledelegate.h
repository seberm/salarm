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


#ifndef SCHEDULEDELEGATE_H
#define SCHEDULEDELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>


class Scheduler;
class SchedulerProxyModel;
class SchedulerModel;


class ScheduleDelegate : public QStyledItemDelegate {
    
	Q_OBJECT
	
public:
    explicit ScheduleDelegate(QObject *parent = 0, SchedulerProxyModel *proxyModel = 0, SchedulerModel *model = 0);
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
	

signals:

public slots:
	
private:
	
	Scheduler *m_scheduler;
	SchedulerProxyModel *m_proxyModel;
	SchedulerModel *m_model;
};

#endif // SCHEDULEDELEGATE_H
