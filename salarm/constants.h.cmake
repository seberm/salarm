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



#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <QString>
#include <QDir>


// Global CONSTANTS
#cmakedefine SALARM_VERSION_MAJOR "${SALARM_VERSION_MAJOR}"
#cmakedefine SALARM_VERSION_MAJOR "${SALARM_VERSION_MINOR}"
#cmakedefine SALARM_VERSION_MAJOR "${SALARM_VERSION_REVISION}"
#cmakedefine SALARM_VERSION_MAJOR "${SALARM_VERSION}"


const QString VERSION = "0.40.0";
const QString NAME = "sAlarm Scheduler";
const QString UNIX_NAME = "salarm";
const QString HOMEPAGE = "http://salarm.seberm.com";
const QString BUGZILLA = "http://bugs.seberm.com";

// Default configuration file definition
const QString CONF_DIR = QDir::homePath().append(QDir::separator()).append(".config");
const QString CONFIG_FILE = QString(CONF_DIR).append(QDir::separator()).append("salarm").append(QDir::separator()).append("main.conf");
const QString SQLITE_DB_FILE = QString(CONF_DIR).append(QDir::separator()).append("salarm").append(QDir::separator()).append("schedules.db");


#endif // CONSTANTS_H
