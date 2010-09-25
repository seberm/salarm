#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QDir>

// Global CONSTS
const QString VERSION = "0.30.0";
const QString NAME = "sAlarm Scheduler";
const QString UNIX_NAME = "salarm";

// Default configuration file definition
const QString CONFIG_FILE = QDir::homePath().append(QDir::separator()).append(".salarm").append(QDir::separator()).append("main.conf");
const QString SQLITE_DB_FILE = QDir::homePath().append(QDir::separator()).append(".salarm").append(QDir::separator()).append("schedules.db");


#endif // CONSTANTS_H
