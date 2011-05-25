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
	
	//! Constructor
	/*!
	  \param scheduler pointer to Scheduler object
	*/
	XmlHandler(Scheduler *scheduler);
	
	//! Called when reader has parsed start element tag
	/*!
	  The reader calls this function when it has parsed a start element tag.
	  If this function returns false the reader stops parsing and reports an error.
	  \param qName name of the start tag
	  \param atts attributes attached to the element
	  \param localName the local name
	  \param namespaceURI namespace URI
	  \sa endElement()
	*/
	bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
	
	//! Called when reader has parsed an end element tag
	/*!
	  The reader calls this function when it has parsed an end element tag.
	  If this function returns false the reader stops parsing and reports an error.
	  \param qName name of the end tag
	  \param atts attributes attached to the element
	  \param localName the local name
	  \param namespaceURI namespace URI
	  \sa startElement()
	*/
	bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
	
	//! Called when reader has parsed a chunk of character data
	/*!
	  The reader calls this function when it has parsed a chunk of character data.
	  If this function returns false the reader stops parsing and reports an error.
      \param characters character data
	*/
	bool characters(const QString &characters);
	
	//! Called when error occorred
	/*!
	  If any of the handler functions returns false.
	  \param exception contains more specific details about error
	*/
	bool fatalError(const QXmlParseException &exception);
	
	
private:
	
	//! Pointer to Schedule object
	Scheduler *m_scheduler;
	
	//! Contains text between tags
	QString m_currentText;
	
	//! Schedule database ID
	quint8 m_scheduleID;
	
	//! Schedule category database ID
	quint8 m_scheduleCategoryID;
	
	//! Schedule category name
	QString m_scheduleCategory;
	
	//! Indicates if schedule is timeouted or not
	bool m_scheduleTimeouted;
	
	//! Schedule title
	QString m_scheduleTitle;
	
	//! Schedule text
	QString m_scheduleText;
	
	//! Keeps schedule expiration date and time
	QDateTime m_scheduleExpiration;
	
};


#endif // XMLHANDLER_H
