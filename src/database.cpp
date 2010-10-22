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



#include "database.h"
#include "constants.h"

#include <QtDebug>
#include <QSettings>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QStringList>

Database::Database(QString name): _name(name) {
	
}


Database::~Database() {
	
	qDebug() << "Closing database connection " << _name;
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	sqlConnection.close();
}


bool Database::dbConnect() {
	qDebug() << "Connecting " << _name;
	
	if (QSqlDatabase::contains(_name)) {
		qDebug() << "Connection " << _name << " already exists.";
		return true;
	}

	QSettings settings(CONFIG_FILE, QSettings::IniFormat, this);
	
	Database::DriverTypes driver;
	switch (settings.value("App/DatabaseDriver", 0).toInt()) {
		default:
		case 0:
			driver = SQLite;
			break;
		case 1:
			driver = MySQL;
			break;
	}
	
	switch (driver) {
		case MySQL: {
			sqlDatabase = QSqlDatabase::addDatabase("QMYSQL", _name);
				
			settings.beginGroup("MySQL");
				sqlDatabase.setHostName(settings.value("HostName", "localhost").toString()); // If "127.0.0.1" is configured, it can causes errors
				sqlDatabase.setUserName(settings.value("UserName", QString()).toString());
				sqlDatabase.setPassword(settings.value("Password", QString()).toString());
				sqlDatabase.setDatabaseName(settings.value("Database", "salarm").toString());
			settings.endGroup();
		} break;
		
		case SQLite: {
				sqlDatabase = QSqlDatabase::addDatabase("QSQLITE", _name);
				sqlDatabase.setDatabaseName(SQLITE_DB_FILE);
		} break;
	}
	
	if (!sqlDatabase.open()) {
		qDebug() << "Cannot connect to database " << sqlDatabase.connectionName();
		qDebug() << "Reason: " << sqlDatabase.lastError().text();
		return false;
	}
	
	// Set MySQL connection encoding
	if (driver == MySQL)
		QSqlQuery query("SET CHARACTER SET utf8;", sqlDatabase);
	
	if (!sqlDatabase.tables(QSql::Tables).contains("Schedules", Qt::CaseSensitive))
		dbInit(driver); // Creates DB table Schedules
	
	return true;
}


void Database::dbInit(Database::DriverTypes dbType) {
	qDebug() << "Initializing database...";
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	switch (dbType) {
		case MySQL: {
			
			QString sql;
			sql = QString(
					"CREATE TABLE IF NOT EXISTS Schedule (" \
					" id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT," \
					" categoryID INT(11) UNSIGNED DEFAULT FALSE," \
					" title VARCHAR(200) NOT NULL," \
					" text TEXT DEFAULT NULL," \
					" datetime DATETIME NOT NULL," \
					" timeouted BOOL NOT NULL DEFAULT FALSE," \
					
					" KEY id (id)" \
					") ENGINE=MyISAM DEFAULT CHARSET=utf8;" \
					
					
					"CREATE TABLE IF NOT EXISTS ScheduleCategory (" \
					" id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT," \
					" name VARCHAR(100) NOT NULL," \
					
					" KEY id (id)" \
					") ENGINE=MyISAM DEFAULT CHARSET=utf8;" \
					
					);
			
			QSqlQuery query(sql, sqlConnection);
			
			if (!query.exec())
				qDebug() << query.lastError();
			
		} break;
		
		case SQLite: {
			
//! \todo Make this part of code more simpler - it's the mess!
				
			QString sql1;
			sql1 = QString (
					"CREATE TABLE IF NOT EXISTS Schedule (" \
					" id INTEGER PRIMARY KEY AUTOINCREMENT," \
					" categoryID INTEGER," \
					" title CHAR(200) NOT NULL," \
					" text TEXT DEFAULT NULL," \
					" datetime DATETIME NOT NULL," \
					" timeouted TINYBOOLEAN NOT NULL DEFAULT 0" \
					
					");" \
					);
			
			QString sql2;
			sql2 = QString(
					"CREATE TABLE IF NOT EXISTS ScheduleCategory (" \
					" id INTEGER PRIMARY KEY AUTOINCREMENT," \
					" name CHAR(100) NOT NULL" \
					
					");" \
					);
	
			QSqlQuery query1(sql1, sqlConnection);
			QSqlQuery query2(sql2, sqlConnection);

			if (!query1.exec())
				qDebug() << query1.lastError();
			
			if (!query2.exec())
				qDebug() << query2.lastError();
			
		} break;
	}
}
