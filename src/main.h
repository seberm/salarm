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


#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QDir>


// Global CONSTS
const QString VERSION = "0.5";
const QString NAME = "sAlarm Scheduler";
const QString UNIX_NAME = "salarm";


// Default configuration file definition
const QString CONFIG_FILE = QDir::homePath().append(QDir::separator()).append(".salarm").append(QDir::separator()).append("main.conf");
const QString SQLITE_DB_FILE = QDir::homePath().append(QDir::separator()).append(".salarm").append(QDir::separator()).append("schedules.db");

#endif // MAIN_H
