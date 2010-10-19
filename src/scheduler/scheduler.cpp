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


#include "scheduler.h"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>


Scheduler::Scheduler(QWidget *parent) : QTreeView(parent) {
	
	QStringList headers;
	headers << "DBID" << tr("Title") << tr("Text") << tr("Expiration") << tr("Category") << "CategoryID";
	_model = new SchedulerModel(headers, this);
	
	_proxyModel = new SchedulerProxyModel(this);
	_proxyModel->setSourceModel(_model);
	
	setModel(_proxyModel);
	
	// Hide the first column that holds DBID
	setColumnHidden(0, true);
	
	// Hide the column with schedule category ID
	setColumnHidden(5, true);
	
	// Allows the sorting in QListView
	setSortingEnabled(true);
	
	setRootIsDecorated(false);
	setAlternatingRowColors(true);	
	
	// We need to update the list of schedules
	refreshSchedules();
	
	_scheduleTimer = new QTimer(this);
	_scheduleTimer->setInterval(1000);
	connect (_scheduleTimer, SIGNAL(timeout()), this, SLOT(checkSchedules()));
	_scheduleTimer->start();
}


void Scheduler::removeSchedule() {
	
	QModelIndex index = selectionModel()->currentIndex();
	
	if (!index.isValid())
		return;
	
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
	QString sql("DELETE FROM Schedule WHERE id = %1;");

	query.prepare(sql.arg(dbID));
	if (!query.exec())
		qDebug() << query.lastError();
	
	// And we refresh the schedules list
	refreshSchedules();
}


void Scheduler::refreshSchedules() {

	// Fist we need to remove all schedules from scheduler
	_model->removeRows(0, _model->rowCount(QModelIndex()));
	_schedules.clear();

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sql("SELECT Schedule.id, Schedule.title, Schedule.text, Schedule.datetime, ScheduleCategory.name, ScheduleCategory.id, Schedule.timeouted" \
				" FROM Schedule" \
				" LEFT JOIN ScheduleCategory" \
				" ON ScheduleCategory.id = Schedule.categoryID" \
				" ORDER BY Schedule.datetime ASC;" \
				);

	QSqlQuery query(sql, sqlConnection);
	
	
	while (query.next()) {
		QModelIndex index = selectionModel()->currentIndex();
		if (!_model->insertRow(index.row() + 1, index.parent()))
			return;

		// DBID
		QModelIndex child = _model->index(index.row() + 1, 0, index.parent());
		_model->setData(child, query.value(0));
		
		// Title
		child = _model->index(index.row() + 1, 1, index.parent());
		_model->setData(child, query.value(1));
		
		// Text
		child = _model->index(index.row() + 1, 2, index.parent());
		_model->setData(child, query.value(2));
		
		// Expiration
		child = _model->index(index.row() + 1, 3, index.parent());
		_model->setData(child, query.value(3));
		
		// Category
		child = _model->index(index.row() + 1, 4, index.parent());
		
		if (query.value(4).toString().length() == 0)
			_model->setData(child, tr("No category"));
		else
			_model->setData(child, query.value(4));
		
		// Schedule category ID
		child = _model->index(index.row() + 1, 5, index.parent());
		_model->setData(child, query.value(5));
		
		// We want only oncoming schedules
		if (!query.value(6).toBool())
			_schedules.append(qMakePair(query.value(0).toInt(), query.value(3).toDateTime()));

	}
}


void Scheduler::checkSchedules() {
	
	for (int i = 0; i < _schedules.length(); i++) {
		
		int scheduleID = _schedules.at(i).first;
		QDateTime d = _schedules.at(i).second;

		if (d < QDateTime::currentDateTime())
			scheduleTimeouted(scheduleID);
	}
}


void Scheduler::scheduleTimeouted(int ID) {
	
	QMessageBox::information(this, tr("Timeouted"), tr("Schedule \"%1\" timeouted!").arg(QString::number(ID)));
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sql = "UPDATE Schedule SET timeouted = 1" \
				  " WHERE id = ?;";

	QSqlQuery query(sqlConnection);
	
	query.prepare(sql);
	query.addBindValue(ID);
	
	if (!query.exec())
		qDebug() << query.lastError();
		
	refreshSchedules();
}
