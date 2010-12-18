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


#include <QtDebug>
#include <QtSql>
#include <QStringList>

#include "database.h"
#include "constants.h"
#include "settings.h"
extern QSettings *g_settings;


Database::Database(QString name): m_name(name) {
	
}


Database::~Database() {
	
	qDebug() << "Closing database connection " << m_name;
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	sqlConnection.close();
}


bool Database::dbConnect() {
	
	qDebug() << "Connecting " << m_name;
	
	if (QSqlDatabase::contains(m_name)) {
		
		qWarning() << "Connection " << m_name << " already exists.";
		return true;
	}
	
	int driver = g_settings->value("App/DatabaseDriver", 0).toInt();	
	switch (driver) {
		
		case MySQL: {
				
			sqlDatabase = QSqlDatabase::addDatabase("QMYSQL", m_name);
				
			g_settings->beginGroup("MySQL");
				sqlDatabase.setHostName(g_settings->value("HostName", "localhost").toString()); // If "127.0.0.1" is configured, it can causes errors
				sqlDatabase.setUserName(g_settings->value("UserName", QString()).toString());
				sqlDatabase.setPassword(g_settings->value("Password", QString()).toString());
				sqlDatabase.setDatabaseName(g_settings->value("Database", "salarm").toString());
			g_settings->endGroup();
		} break;
		
		case SQLite: {
				
				sqlDatabase = QSqlDatabase::addDatabase("QSQLITE", m_name);
				sqlDatabase.setDatabaseName(SQLITE_DB_FILE);
		} break;
	}
	
	if (!sqlDatabase.open()) {
		
		qCritical() << "Cannot connect to database " << sqlDatabase.connectionName();
		qCritical() << "Reason: " << sqlDatabase.lastError().text();
		return false;
	}
	
	// Set MySQL connection encoding
	if (driver == MySQL)
		QSqlQuery query("SET CHARACTER SET utf8;", sqlDatabase);
	
	if (!sqlDatabase.tables(QSql::Tables).contains("Schedules", Qt::CaseSensitive))
		dbInit(driver); // Creates DB table Schedules
	
	return true;
}


void Database::dbInit(int dbType) {
	
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
				qWarning() << query.lastError();
			
		} break;
		
		case SQLite: {
			
			QStringList tables;
			tables
				<<  "CREATE TABLE IF NOT EXISTS Schedule (" \
					" id INTEGER PRIMARY KEY AUTOINCREMENT," \
					" categoryID INTEGER," \
					" title CHAR(200) NOT NULL," \
					" text TEXT DEFAULT NULL," \
					" datetime DATETIME NOT NULL," \
					" timeouted TINYBOOLEAN NOT NULL DEFAULT 0" \
					");"
				<<					
					"CREATE TABLE IF NOT EXISTS ScheduleCategory (" \
					" id INTEGER PRIMARY KEY AUTOINCREMENT," \
					" name CHAR(100) NOT NULL" \
					");"
			;
			
			// The SQLite needs to create the database tables individually
			for (int i = 0; i < tables.size(); i++) {
	
				QSqlQuery query(tables.at(i), sqlConnection);

				if (!query.exec())
					qWarning() << query.lastError();
			}
			
		} break;
	}
}
