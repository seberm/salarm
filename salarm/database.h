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



#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


class Database : public QObject {
	
	Q_OBJECT
	Q_ENUMS(DriverTypes)
			
	public:
		Database(QString connName = "");
		~Database();
		QSqlDatabase sqlDatabase;
		bool connect();
		enum DriverTypes { SQLite, MySQL };
		
		inline QString connectionName() const { return m_dbName; }
		inline DriverTypes driverType() const { return m_driverType; }
		inline QSqlDatabase sqlDb() { return *m_sqlDb; }
		
	private:
		// Name of connection
		QString m_dbName;
		
		QString m_hostname;
		QString m_username;
		QString m_password;
		QString m_database;
		DriverTypes m_driverType;
		
		QSqlDatabase *m_sqlDb;
		
		void dbInit();
};

#endif // DATABASE_H
