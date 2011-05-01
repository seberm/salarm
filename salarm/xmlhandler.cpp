#include "xmlhandler.h"
#include "scheduler.h"
#include "schedule.h"


XmlHandler::XmlHandler(Scheduler *scheduler) {
	
	m_scheduler = scheduler;
	m_schedule = new Schedule;
}


bool XmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) {
	
	if (qName == "schedule") {
		
		
	}
}


bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {
	
	
}


bool XmlHandler::characters(const QString &ch) {
	
	
}


bool XmlHandler::fatalError(const QXmlParseException &exception) {
	
	
}
