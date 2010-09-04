#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QTreeWidgetItem>
#include <QDateTime>

class Schedule : /*public QObject, */public QTreeWidgetItem {
//Q_OBJECT
public:
	//! Constructor
	/*!
		\param rowID The database row ID
		\param title Schedule's title
		\param expiration
	*/
	//explicit Schedule(QTreeWidgetItem *parent);
	explicit Schedule(int rowID, const QString &title, const QString &text, QDateTime expiration);
	
	~Schedule();
	
	/*virtual*/ int dbID();


private:
	//! Database row ID
	int _rowID;
	QString _title;
	QString _text;
	QDateTime _expiration;

};

#endif // SCHEDULE_H
