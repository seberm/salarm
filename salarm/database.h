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


#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


//! Database objects handles connection to database
/*!
  Database class is used for establishing database connection.
*/
class Database : public QObject {
	
	Q_OBJECT
	Q_ENUMS(DriverTypes)
			
	public:
		
		//! Enumerates supported database backends
		/*!
		  DriverTypes provide enumeration of supported database drivers.
		  \sa driverType()
		*/
		enum DriverTypes { SQLite, MySQL };
		
		//! Constructor
		/*!
		  Initializes the database. Recieves connection name as parameter.
		  \param connName database connection name
		  \sa connectionName()
		*/
		Database(QString connName = "");
		
		//! Destructor
		~Database();
		
		//! Connects the database
		/*!
		  \return Returns true if connection was successful
		*/
		bool connect();
		
		//! Returns database connection name
		/*!
		  \return Returns the database connection name
		*/
		inline QString connectionName() const { return m_dbName; }
		
		//! Returns current driver type
		/*!
		  \return Returns current database driver type
		*/
		inline DriverTypes driverType() const { return m_driverType; }
		
		//! Returns pointer to QSqlDatabase
		/*!
		  \return Returns pointer to QSqlDatabase object
		*/
		inline QSqlDatabase *sqlDb() { return m_sqlDb; }

		
	private:
		
		//! Check if the database contains all required tables and if not creates them
		/*!
		  Checks the structure of tables.
		*/
		void dbInit();
		
		
		//! Name of database connection
		QString m_dbName;
		
		//! Database hostname
		QString m_hostname;
		
		//! Database username
		QString m_username;
		
		//! Database password
		QString m_password;
		
		//! Database name
		QString m_database;
		
		//! Database driver type
		DriverTypes m_driverType;
		
		//! Pointer to QSqlDatabase
		QSqlDatabase *m_sqlDb;
};

#endif // DATABASE_H
