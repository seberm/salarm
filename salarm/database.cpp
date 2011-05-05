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


#include <QtDebug>
#include <QtSql>
#include <QStringList>
#include <QHostAddress>
#include <QFile>

#include "database.h"
#include "constants.h"
#include "settings.h"
extern QSettings *g_settings;


Database::Database(QString connName) {
	
	m_sqlDb = NULL;
	
	m_dbName = connName;
	g_settings->beginGroup("App");
		m_driverType = static_cast<DriverTypes>(g_settings->value("DatabaseDriver", 0).toInt());
	g_settings->endGroup();
	
	g_settings->beginGroup("MySQL");
		m_hostname = g_settings->value("HostName", QHostAddress::LocalHost).toString();
		m_username = g_settings->value("UserName", QString()).toString();
		m_password = g_settings->value("Password", QString()).toString();
		m_database = g_settings->value("Database", "salarm").toString();
	g_settings->endGroup();
}


Database::~Database() {
	
	qDebug() << tr("closing database connection %1").arg(m_dbName);
	
	delete m_sqlDb;
	QSqlDatabase::removeDatabase(m_dbName);
}


bool Database::connect() {
	
	qDebug() << tr("connecting %1").arg(m_dbName);
	
	if (QSqlDatabase::contains(m_dbName)) {
		
		qWarning() << tr("connection %1 already exists").arg(m_dbName);
		return true;
	}
	
	switch (m_driverType) {
		
		case MySQL: {
				
			m_sqlDb = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", m_dbName));
				
			m_sqlDb->setHostName(m_hostname); // If m_hostname is "127.0.0.1" , it can cause errors
			m_sqlDb->setUserName(m_username);
			m_sqlDb->setPassword(m_password);
			m_sqlDb->setDatabaseName(m_database);
		} break;
		
		case SQLite: {
		
			m_sqlDb = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", m_dbName));
				
			if (!QFile::exists(SQLITE_DB_FILE)) {
					
				QString confDirPath = CONF_DIR + QDir::separator() + UNIX_NAME;
				QDir salarmDir;
				if (!salarmDir.exists(confDirPath))
					salarmDir.mkdir(confDirPath);
					
				QFile conf(SQLITE_DB_FILE);
				if (!conf.open(QIODevice::WriteOnly)) {
						
					qCritical() << tr("failed to create SQLite database file");
					return false;
				}
			}
					
			m_sqlDb->setDatabaseName(SQLITE_DB_FILE);
		} break;
	}
	
	if (!m_sqlDb->open()) {
		
		qCritical() << tr("cannot connect to database %1").arg(m_sqlDb->connectionName());
		qCritical() << tr("reason: %1").arg(m_sqlDb->lastError().text());
		m_sqlDb = NULL;
		
		return false;
	}
	
	// Set MySQL connection encoding
	if (m_driverType == MySQL) {
		
		QSqlQuery query("SET CHARACTER SET utf8;", *m_sqlDb);
		query.exec();
	}
	
	QStringList tables = m_sqlDb->tables(QSql::AllTables);
	if (!(tables.contains("Schedule") &&
		  tables.contains("ScheduleCategory"))) {
		
		dbInit(); // Creates DB tables
	}
	
	return true;
}


void Database::dbInit() {
	
	qDebug() << tr("initializing database...");
	
	QSqlQuery query(*m_sqlDb);
	
	switch (m_driverType) {
		
		case MySQL: {
			
			query.exec("DROP TABLE IF EXISTS `Schedule`, `ScheduleCategory`;");
			
			query.exec(
					"CREATE TABLE IF NOT EXISTS `Schedule` (" \
					" `id` int(11) NOT NULL AUTO_INCREMENT," \
					" `categoryID` int(11) UNSIGNED DEFAULT FALSE," \
					" `title` varchar(250) NOT NULL," \
					" `text` text DEFAULT NULL," \
					" `datetime` datetime NOT NULL," \
					" `timeouted` bool NOT NULL DEFAULT FALSE," \
					" PRIMARY KEY (`id`)" \
					") ENGINE=MyISAM DEFAULT CHARSET=utf8;" \
					);
					
			query.exec(
					"CREATE TABLE IF NOT EXISTS `ScheduleCategory` (" \
					" `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT," \
					" `name` varchar(255) NOT NULL," \
					" PRIMARY KEY (`id`)" \
					") ENGINE=MyISAM DEFAULT CHARSET=utf8;" \
					);
			
		} break;
		
		case SQLite: {
			
			query.exec("DROP TABLE IF EXISTS `Schedule`;");
			query.exec("DROP TABLE IF EXISTS `ScheduleCategory`;");
			
			// The SQLite needs to create the database tables individually - it's not possible to create tables in one query
			query.exec(
					"CREATE TABLE IF NOT EXISTS `Schedule` (" \
					" `id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
					" `categoryID` INTEGER," \
					" `title` CHAR(200) NOT NULL," \
					" `text` TEXT DEFAULT NULL," \
					" `datetime` DATETIME NOT NULL," \
					" `timeouted` TINYBOOLEAN NOT NULL DEFAULT (0)" \
					");" \
					);
							
			query.exec(
					"CREATE TABLE IF NOT EXISTS ScheduleCategory (" \
					" id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
					" name CHAR(100) NOT NULL" \
					");" \
					);
			;
	
			
		} break;
	}
}
