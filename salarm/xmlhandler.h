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


#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QDateTime>
#include <QXmlDefaultHandler>

class Scheduler;

class XmlHandler : public QXmlDefaultHandler {
	
	
	
public:
	XmlHandler(Scheduler *scheduler);
	bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
	bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
	bool characters(const QString &ch);
	bool fatalError(const QXmlParseException &exception);
	
	
private:
	Scheduler *m_scheduler;
	
	QString m_currentText;
	
	
	quint8 m_scheduleID;
	quint8 m_scheduleCategoryID;
	QString m_scheduleCategory;
	bool m_scheduleTimeouted;
	QString m_scheduleTitle;
	QString m_scheduleText;
	QDateTime m_scheduleExpiration;
	
};


#endif // XMLHANDLER_H
