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



#include "constants.h"


#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QLocale>
#include <QtDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDir>

int main(int argc, char *argv[]) {

	// Initiating the application
    QApplication salarm(argc, argv);
	
	salarm.setOrganizationName("Šabart Otto");
	salarm.setApplicationName(NAME);
	salarm.setApplicationVersion(VERSION);

	// Initiating a application global translator
	QTranslator translator;
	{
		QString locale = QLocale::system().name();
		qDebug() << "Current locale" << locale;
		QString localeDir = qApp->applicationDirPath() + QDir::separator() + "src" + QDir::separator() + "locale";
		translator.load(locale, localeDir);
		salarm.installTranslator(&translator);
	}
	
	MainWindow w;
	w.show();
	
    return salarm.exec();
}
