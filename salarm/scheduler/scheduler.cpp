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


#include <QDebug>
#include <QtSql>
#include <QMessageBox>

#include "settings.h"
extern QSettings *g_settings;
#include "scheduler.h"
#include "schedulermodel.h"
#include "constants.h"
#include "schedulerproxymodel.h"
#include "scheduledelegate.h"
#include "schedule.h"
#include "database.h"

// Columns definition
Column DBID =			{ 0, "DBID" };
Column CategoryID =	{ 1, "CategoryID" };
Column Status =		{ 2, "" };
Column Title =		{ 3, QObject::tr("Title") };
Column Text =			{ 4, QObject::tr("Text") };
Column Expiration =	{ 5, QObject::tr("Expiration") };
Column Category =		{ 6, QObject::tr("Category") };

int COLUMN_COUNT = 7;


Scheduler::Scheduler(Database *sqlDb, QWidget *parent) : QTreeView(parent) {
	
	m_sqlDb = sqlDb;
	
	QStringList headers;
	headers << DBID.columnName
			<< CategoryID.columnName
			<< Status.columnName
			<< Title.columnName
			<< Text.columnName
			<< Expiration.columnName
			<< Category.columnName;
			
	m_model = new SchedulerModel(headers, this);
	
	m_proxyModel = new SchedulerProxyModel(this);
	m_proxyModel->setSourceModel(m_model);
	
	setModel(m_proxyModel);
	
	// Hide the first column that holds DBID
	setColumnHidden(DBID.columnID, true);
	
	// Hide the column with schedule category ID
	setColumnHidden(CategoryID.columnID, true);
	
	// Allow the sorting in QTreeView
	setSortingEnabled(true);

	// Set the item delegate
	m_itemDelegate = new ScheduleDelegate(this, m_proxyModel, m_model);
	setItemDelegate(m_itemDelegate);
	
	setRootIsDecorated(false);
	setAlternatingRowColors(true);	
	
	// Resize columns to their content
	setColumnWidth(Status.columnID, 20);
	resizeColumnToContents(Title.columnID);
	resizeColumnToContents(Expiration.columnID);
	
	// We need to update the list of schedules
	refreshSchedules();
	
	makeConnections();
	
	m_scheduleTimer = new QTimer(this);
	m_scheduleTimer->setInterval(1000);
	connect (m_scheduleTimer, SIGNAL(timeout()), this, SLOT(checkSchedules()));
	m_scheduleTimer->start();
}


Scheduler::~Scheduler() {
	
}


void Scheduler::makeConnections() {
	
	// If some schedule timeouted we need to refresh the schedule list
//	connect (this, SIGNAL(scheduleTimeouted(int)), this, SLOT(refreshSchedules()));
}


void Scheduler::removeSchedule() {
	
	QModelIndex index = selectionModel()->currentIndex();
	
	if (!index.isValid())
		return;
	
	// Read DBID from the hidden first column
	int dbID = index.sibling(index.row(), DBID.columnID).data().toInt();

	QMessageBox msg(this);
		msg.setWindowTitle(tr("Remove schedule"));
		msg.setText(tr("Really want to remove schedule?"));
		msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	
	if (msg.exec() == QMessageBox::No)
		return;

	
	QSqlQuery query(m_sqlDb->sqlDb());
	QString sql("DELETE FROM Schedule WHERE id = %1;");

	query.prepare(sql.arg(dbID));
	if (!query.exec())
		qWarning() << query.lastError();
	
	// We refresh the schedules list
	refreshSchedules();
	
	// And set new current index
	QModelIndex subIndex = m_model->index(index.row() - 1, index.column());
	setCurrentIndex(subIndex);
}


void Scheduler::refreshSchedules() {

	qDebug() << tr("refreshing schedules ...");
	
	// Fist we need to remove all schedules from scheduler
	m_model->removeRows(0, m_model->rowCount(QModelIndex()));
	m_schedules.clear();
	
	QString sql("SELECT Schedule.id AS DBID, Schedule.title, Schedule.text, Schedule.datetime, ScheduleCategory.name, ScheduleCategory.id AS categoryID, Schedule.timeouted" \
				" FROM Schedule" \
				" LEFT JOIN ScheduleCategory" \
				" ON ScheduleCategory.id = Schedule.categoryID" \
				" ORDER BY Schedule.datetime ASC;" \
				);

	QSqlQuery query(sql, m_sqlDb->sqlDb());
	
	int dbDBID = query.record().indexOf("DBID");
	int dbTitle = query.record().indexOf("title");
	int dbText = query.record().indexOf("text");
	int dbExpiration = query.record().indexOf("datetime");
	int dbCategoryName = query.record().indexOf("name");
	int dbCategoryID = query.record().indexOf("categoryID");
	int dbTimeouted = query.record().indexOf("timeouted");
	
	while (query.next()) {
		
		QModelIndex index = selectionModel()->currentIndex();
		if (!m_model->insertRow(index.row() + 1, index.parent()))
			return;

		// DBID
		QModelIndex child = m_model->index(index.row() + 1, DBID.columnID, index.parent());
		m_model->setData(child, query.value(dbDBID));
		
//! \todo dodelat ikonu u upominek		
		// Status
		QImage image(":/statusIcons/checkIcon");
		
		child = m_model->index(index.row() + 1, Status.columnID, index.parent());
		m_model->setData(child, image, Qt::DisplayRole);
		
		// Title
		child = m_model->index(index.row() + 1, Title.columnID, index.parent());
		m_model->setData(child, query.value(dbTitle));
		
		// Text
		child = m_model->index(index.row() + 1, Text.columnID, index.parent());
		m_model->setData(child, query.value(dbText));
		
		// Expiration
		child = m_model->index(index.row() + 1, Expiration.columnID, index.parent());
		m_model->setData(child, query.value(dbExpiration));
		
		// Category
		child = m_model->index(index.row() + 1, Category.columnID, index.parent());
		
		if (query.value(4).toString().length() == 0)
			m_model->setData(child, tr("No category"));
		else
			m_model->setData(child, query.value(dbCategoryName));
		
		// Schedule category ID
		child = m_model->index(index.row() + 1, CategoryID.columnID, index.parent());
		m_model->setData(child, query.value(dbCategoryID));
		
		// We want to have in m_schedules only oncoming schedules
		if (!query.value(dbTimeouted).toBool())
			m_schedules.append(qMakePair(query.value(dbDBID).toInt(), query.value(dbExpiration).toDateTime()));

	}
}


void Scheduler::checkSchedules() {
	
	for (int i = 0; i < m_schedules.length(); i++) {
		
		int scheduleID = m_schedules.at(i).first;
		QDateTime d = m_schedules.at(i).second;

		if (d < QDateTime::currentDateTime())
			emit scheduleTimeouted(scheduleID);
	}
}


void Scheduler::markTimeouted(int id) {
	
	QString sqlUpdate = "UPDATE Schedule SET timeouted = 1" \
						" WHERE id = ?;";

	QSqlQuery queryUpdate(sqlUpdate, m_sqlDb->sqlDb());
	
	queryUpdate.prepare(sqlUpdate);
	queryUpdate.addBindValue(id);
	
	if (!queryUpdate.exec())
		qWarning() << queryUpdate.lastError();
	
	refreshSchedules();
}


void Scheduler::postpone(int id) {

	g_settings->beginGroup("App");
		g_settings->beginGroup("Postpone");
			int hours = g_settings->value("Hour").toInt();
			int minutes = g_settings->value("Minute").toInt();
			int seconds = g_settings->value("Second").toInt();
		g_settings->endGroup();
	g_settings->endGroup();

	QDateTime newDateTime = QDateTime::currentDateTime();
	newDateTime = newDateTime.addSecs(hours*60*60 + minutes*60 + seconds);
	
	QString sqlUpdate = "UPDATE Schedule SET datetime = ?" \
						" WHERE id = ?;";

	QSqlQuery queryUpdate(sqlUpdate, m_sqlDb->sqlDb());
	
	queryUpdate.prepare(sqlUpdate);
	queryUpdate.addBindValue(newDateTime);
	queryUpdate.addBindValue(id);
	
	if (!queryUpdate.exec())
		qWarning() << queryUpdate.lastError();
	
	refreshSchedules();
}


void Scheduler::addSchedule(const QString &title, const QString &text, const QDateTime &expiration, int categoryID) {
	
	if (title.isEmpty()) {
		
		qWarning() << tr("cannot add schedule - title is empty");
		return;
	}
	
	if (!expiration.isValid()) {
	
		qWarning() << tr("cannot add schedule - expiration date is not valid");
		return;
	}
	
	
	QSqlQuery query(m_sqlDb->sqlDb());
	
	QString sql;
	sql = "INSERT INTO Schedule (title, text, datetime, categoryID)" \
		  " VALUES(:title, :text, :datetime, :categoryID)";

	query.prepare(sql);
	
	query.bindValue(0, title.simplified());
	query.bindValue(1, text.simplified());
	query.bindValue(2, expiration);
	query.bindValue(3, categoryID);
	
	if (!query.exec())
		qWarning() << query.lastError();
	
	refreshSchedules();
}


void Scheduler::addSchedule(Schedule *s) {
	
	//! \todo It's neccessary to edit Schedule class and adapt it	
	//addSchedule(s->title(), s->text(), s->expiration(), s->category());
}


void Scheduler::editSchedule(int id, const QString &title, const QString &text, const QDateTime &expiration, int categoryID) {
	
	QSqlQuery query(m_sqlDb->sqlDb());
	
	QString sql;	
	
	sql = "UPDATE Schedule SET title = :title, text = :text, datetime = :datetime, categoryID = :categoryID, timeouted = 0" \
		  " WHERE id = ?;";

	query.prepare(sql);
	
	query.bindValue(0, title.simplified());
	query.bindValue(1, text.simplified());
	query.bindValue(2, expiration);
	query.bindValue(3, categoryID);
	query.bindValue(4, id);
	
	if (!query.exec())
		qWarning() << query.lastError();

	refreshSchedules();
}


void Scheduler::generateXmlToFile(QFile *file) {
	
	QString sql("SELECT Schedule.id AS DBID, Schedule.title, Schedule.text, Schedule.datetime, ScheduleCategory.name, ScheduleCategory.id AS categoryID, Schedule.timeouted" \
				" FROM Schedule" \
				" LEFT JOIN ScheduleCategory" \
				" ON ScheduleCategory.id = Schedule.categoryID" \
				" ORDER BY Schedule.datetime ASC;" \
				);

	QSqlQuery query(sql, m_sqlDb->sqlDb());
	
	int dbDBID = query.record().indexOf("DBID");
	int dbTitle = query.record().indexOf("title");
	int dbText = query.record().indexOf("text");
	int dbExpiration = query.record().indexOf("datetime");
	int dbCategoryName = query.record().indexOf("name");
	int dbCategoryID = query.record().indexOf("categoryID");
	int dbTimeouted = query.record().indexOf("timeouted");

	if (!file->open(QFile::WriteOnly)) {
		
		QMessageBox::warning(this, tr("Open error"), tr("Open file for write failed"));
		return;
	}
	
	QTextStream xml(file);
	xml.setCodec("utf-8");
	
	// Writes XML header
	xml << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<schedules>\n";
	
	while (query.next()) {
		
//! @todo It's necessary to escape variables with Qt::escape - it's not working -> Why?
		xml << "<schedule id=\"" << query.value(dbDBID).toInt() << "\" category=\"" << query.value(dbCategoryID).toInt() << "\" timeouted=\"" << query.value(dbTimeouted).toInt() << "\">\n"
		    << "	<title>" << query.value(dbTitle).toString() << "</title>\n"
			<< "	<category>" << query.value(dbCategoryName).toString() << "</category>\n"
		    << "	<text>" << query.value(dbText).toString() << "</text>\n"
			<< "	<expiration>" << query.value(dbExpiration).toString() << "</expiration>\n"
			<< "</schedule>\n";
	}
	
	xml << "</schedules>";
	
	file->close();
	
	QMessageBox::information(this, tr("XML Generated"), tr("XML was successfuly generated"));
}
