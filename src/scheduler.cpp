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
	setModel(_model);
	//for (int column = 0; column < _model->columnCount(QModelIndex()); ++column)
		//resizeColumnToContents(column);

	
	// Hide the first column that holds DBID
	setColumnHidden(0, true);
	
	_db = new Database ("Schedules");
	
	if (_db->dbConnect())
		qDebug() << "Successfuly connected - " << _db->getConnectionName();
	else {
		qDebug() << "Error in connection - " << _db->getConnectionName();
		return;
	}
	
	// We need to update the list of schedules
	refreshSchedules();
}

/*
void Scheduler::removeSchedule(QTreeWidgetItem *i) {

	QMessageBox msg(this);
	msg.setWindowTitle(tr("Remove schedule"));
	msg.setText(tr("Really want to remove this schedule?"));
	msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	
	if (msg.exec() == QMessageBox::No)
		return;
	
        // Read DBID from the hidden first column
        int dbID = i->data(0,Qt::EditRole).toInt();

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	QString sql("DELETE FROM Schedules WHERE id = %1;");

	query.prepare(sql.arg(dbID));
	if (!query.exec())
		qDebug() << query.lastError();
	
	takeTopLevelItem(indexOfTopLevelItem(i));
}
*/

void Scheduler::refreshSchedules() {

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sql("SELECT id,title, text, datetime FROM Schedules;");
	QSqlQuery query(sql, sqlConnection);
	
	
	while (query.next()) {
		/*QStringList strs;
                strs << query.value(0).toString()
			 << query.value(1).toString()
                         << query.value(2).toString()
                         << query.value(3).toString();
		
		QTreeWidgetItem *item = new QTreeWidgetItem(this, strs);
		items.append(item);
		*/
		
		QModelIndex index = selectionModel()->currentIndex();
		if (!_model->insertRow(index.row() + 1, index.parent()))
			return;
			
		/*
		for (int column = 0; column < _model->columnCount(index.parent()); ++column) {
			QModelIndex child = _model->index(index.row() + 1, column, index.parent());
			_model->setData(child, query.value(column).toByteArray(), Qt::EditRole);
		}
		*/
		
		QModelIndex child = _model->index(index.row() + 1, 0, index.parent());
		_model->setData(child, query.value(0).toInt());
		
		child = _model->index(index.row() + 1, 1, index.parent());
		_model->setData(child, query.value(1).toString());
		
		child = _model->index(index.row() + 1, 2, index.parent());
		_model->setData(child, query.value(2).toString());
		
		child = _model->index(index.row() + 1, 3, index.parent());
		_model->setData(child, query.value(3).toDateTime());
		
	}
	
}



