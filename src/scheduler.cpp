
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "scheduler.h"


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

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	query.prepare("INSERT INTO Schedules (title, text, datetime)" \
				  "VALUES(:title, :text, :datetime)");
	
	query.bindValue(0, title);
	query.bindValue(1, text);
	query.bindValue(2, expiration);
	
	if (!query.exec())
		qDebug() << query.lastError();

        QStringList strs;
        // Insert data: DBID, title, text, date
        strs << query.lastInsertId().toString() << title << text << expiration.toString();

        QTreeWidgetItem *item = new QTreeWidgetItem(this, strs);
        insertTopLevelItem(0, item);

	
	emit (changed());
}


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
        QString sql("SELECT id,title, text, datetime FROM Schedules;");
	QSqlQuery query(sql, sqlConnection);
	
	QList<QTreeWidgetItem*> items;
	while (query.next()) {
		QStringList strs;
                strs << query.value(0).toString()
			 << query.value(1).toString()
                         << query.value(2).toString()
                         << query.value(3).toString();
		
		QTreeWidgetItem *item = new QTreeWidgetItem(this, strs);
		items.append(item);
	}
	
	insertTopLevelItems(0, items);
}
