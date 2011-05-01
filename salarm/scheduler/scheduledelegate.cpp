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


#include <QRect>
#include <QtDebug>

#include "scheduledelegate.h"
#include "scheduler.h"
extern const Column Expiration;
extern const Column Status;

#include "schedulerproxymodel.h"
#include "schedulermodel.h"
#include "settings.h"
extern QSettings *g_settings;


ScheduleDelegate::ScheduleDelegate(QObject *parent, SchedulerProxyModel *proxyModel, SchedulerModel *model) : QStyledItemDelegate(parent) {
	
	m_scheduler = dynamic_cast<Scheduler*> (parent);
	m_proxyModel = proxyModel;
	m_model = model;
}


void ScheduleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const {
	
	QRect rect(option.rect);
	
	painter->setFont(option.font);
	painter->setPen(option.palette.text().color());
	
	if (option.state & QStyle::State_Selected) {
		
		painter->fillRect(rect, option.palette.link());
		painter->setPen(option.palette.highlightedText().color());
	}
	
	QModelIndex expirationIndex = index.model()->index(index.row(), Expiration.columnID);
	QDateTime expiration = expirationIndex.data().toDateTime();
	
	// We draw the text into index which we can convert into String
	if (qVariantCanConvert<QString>(index.data())) {
		
		if (expiration < QDateTime::currentDateTime())
			painter->setPen(g_settings->value("GUI/ExpiredScheduleColor", Qt::white).value<QColor>());
		
		painter->drawText(rect,
						  option.fontMetrics.elidedText(index.data().toString(),
														Qt::ElideRight,
														m_scheduler->columnWidth(index.column()))
						 );
		
	} else if (expiration < QDateTime::currentDateTime()) {
		
		QImage img = index.data().value<QImage>();
		painter->drawImage(rect, img);
	}
}
