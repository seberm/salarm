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
#include <QMessageBox>


#include "xmlhandler.h"
#include "scheduler.h"


XmlHandler::XmlHandler(Scheduler *scheduler) {
	
	m_scheduler = scheduler;
}


bool XmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) {

	if (qName == "schedule") {
		
		m_scheduleID = atts.value("id").toInt();
		m_scheduleCategoryID = atts.value("category").toInt();
	}
	
	
//! \todo m_currentText se mozna muze smazat globalne...a ne takto jednotlive!
	if (qName == "title")
		m_currentText.clear();
	
	if (qName == "category")
		m_currentText.clear();
	
	if (qName == "expiration")
		m_currentText.clear();
	
	return true;
}


bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {

	if (qName == "title")
		m_scheduleTitle = m_currentText;
	
	if (qName == "category")
		m_scheduleCategory = m_currentText;
	
	if (qName == "expiration")
		m_scheduleExpiration = QDateTime::fromString(m_currentText, Qt::ISODate);
	
	if (qName == "schedule")
		m_scheduler->addSchedule(m_scheduleTitle, m_scheduleText, m_scheduleExpiration);
	
	return true;
}


bool XmlHandler::characters(const QString &characters) {


	m_currentText = characters;
	
	return true;
}


bool XmlHandler::fatalError(const QXmlParseException &exception) {
	
	QMessageBox::warning(0,
	                     QObject::tr("XML parse error"),
						 QObject::tr("Parse error at  line %1, column %2:\n%3.")
									.arg(exception.lineNumber())
									.arg(exception.columnNumber())
									.arg(exception.message()));
	
	return false;
}
