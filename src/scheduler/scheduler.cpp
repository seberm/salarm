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


#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "scheduler.h"


Scheduler::Scheduler(QWidget *parent) : QTreeView(parent) {
	
	QStringList headers;
	headers << "DBID" << tr("Title") << tr("Text") << tr("Expiration");
	_model = new SchedulerModel(headers, this);
	
	_proxyModel = new SchedulerProxyModel(this);
	_proxyModel->setSourceModel(_model);
	
	setModel(_proxyModel);
	
	// Hide the first column that holds DBID
//	setColumnHidden(0, true);
	
	// Allows the sorting in QListView
	setSortingEnabled(true);
	
	setRootIsDecorated(false);	
	setAlternatingRowColors(true);	
	
	// We need to update the list of schedules
	refreshSchedules();
}


void Scheduler::removeSchedule() {
	
	QModelIndex index = selectionModel()->currentIndex();
	
	// Read DBID from the hidden first column
	int dbID = index.sibling(index.row(), 0).data().toInt();

	QMessageBox msg(this);
		msg.setWindowTitle(tr("Remove schedule"));
		msg.setText(tr("Really want to remove schedule?"));
		msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	
	if (msg.exec() == QMessageBox::No)
		return;

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	QString sql("DELETE FROM Schedules WHERE id = %1;");

	query.prepare(sql.arg(dbID));
	if (!query.exec())
		qDebug() << query.lastError();
	
	// And we refresh the schedules list
	refreshSchedules();
}


void Scheduler::refreshSchedules() {
	
	// Fist we need to remove all schedules from scheduler
	_model->removeRows(0, _model->rowCount(QModelIndex()));

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sql("SELECT id,title, text, datetime FROM Schedules;");
	QSqlQuery query(sql, sqlConnection);
	
	
	while (query.next()) {
		QModelIndex index = selectionModel()->currentIndex();
		if (!_model->insertRow(index.row() + 1, index.parent()))
			return;
		
		// DBID
		QModelIndex child = _model->index(index.row() + 1, 0, index.parent());
		_model->setData(child, query.value(0).toInt());
		
		// Title
		child = _model->index(index.row() + 1, 1, index.parent());
		_model->setData(child, query.value(1).toString());
		
		// Text
		child = _model->index(index.row() + 1, 2, index.parent());
		_model->setData(child, query.value(2).toString());
		
		// Expiration
		child = _model->index(index.row() + 1, 3, index.parent());
		_model->setData(child, query.value(3).toDateTime());
	}
}



