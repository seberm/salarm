
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "scheduler.h"
#include "schedule.h"


Scheduler::Scheduler(QWidget *parent) : QTreeWidget(parent) {
	
	_db = new Database ("Schedules");
	
	if (_db->dbConnect())
		qDebug() << "Successfuly connected - " << _db->getConnectionName();
	else {
		qDebug() << "Error in connection - " << _db->getConnectionName();
		return;
	}
		
	connect(this, SIGNAL(changed()), this, SLOT(refreshSchedules()));
		
	// We need to update the list
	refreshSchedules();
}


void Scheduler::addSchedule(const QString &title, const QString &text, QDateTime expiration) {
	QStringList strs;
	strs << title << text << expiration.toString();
	
	QTreeWidgetItem *item = new QTreeWidgetItem(this, strs);
	insertTopLevelItem(0, item);
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	query.prepare("INSERT INTO Schedules (title, text, datetime)" \
				  "VALUES(:title, :text, :datetime)");
	
	query.bindValue(0, title);
	query.bindValue(1, text);
	query.bindValue(2, expiration);
	
	if (!query.exec())
		qDebug() << query.lastError();
	
	emit (changed());
}


void Scheduler::removeSchedule(QTreeWidgetItem *i) {

	QMessageBox msg(this);
	msg.setWindowTitle(tr("Remove schedule"));
	msg.setText(tr("Really want to remove this schedule?"));
	msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	
	if (msg.exec() == QMessageBox::No)
		return;
	
	Schedule *sch = dynamic_cast<Schedule*>(i);
	int dbID = 0;
	if (sch != NULL)
		dbID = sch->dbID(); 
	else return;

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	QString sql("DELETE FROM Schedules WHERE id = %1;");
	
qDebug() << sql;

	query.prepare(sql.arg(dbID));
	if (!query.exec())
		qDebug() << query.lastError();
	
	takeTopLevelItem(indexOfTopLevelItem(i));
	
	emit (changed());
}


void Scheduler::refreshSchedules() {

	// Removes all schedules from list
	clear();
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QString sql("SELECT title, text, datetime FROM Schedules;");
	QSqlQuery query(sql, sqlConnection);
	
	QList<QTreeWidgetItem*> items;
	while (query.next()) {
		QStringList strs;
		strs << query.value(0).toString()
			 << query.value(1).toString()
			 << query.value(2).toString();
		
		QTreeWidgetItem *item = new QTreeWidgetItem(this, strs);
		items.append(item);
	}
	
	insertTopLevelItems(0, items);
}
