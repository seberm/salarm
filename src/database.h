/*
 * sAlarm - Scheduler
 * http://seberm.homelinux.org/salarm
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
#include <QSettings>
#include <QtSql/QSqlDatabase>

class Database : public QObject {
	Q_OBJECT
	Q_ENUMS(DriverTypes)
	
	public:
		enum DriverTypes { SQLite, MySQL };
		
		Database(QString name = "");
		~Database();
		QSqlDatabase sqlDatabase;
		bool dbConnect();
		QString getConnectionName();
		
	private:
		// Name of connection
		QString _name;
		
		void dbInit(Database::DriverTypes);
};

#endif // DATABASE_H
