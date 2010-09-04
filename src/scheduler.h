#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QTreeWidget>
#include <QDateEdit>

#include "database.h"


class Scheduler : public QTreeWidget {
	
Q_OBJECT

public:
    explicit Scheduler(QWidget *parent = 0);
	//~Scheduler();
	
	//! Adds a new schedule into the list and DB
	void addSchedule(const QString &title, const QString &text, QDateTime expiration);
			
	//! Removes schedule
	void removeSchedule(QTreeWidgetItem *i);
	
	
public slots:	
	//! Updates a list of schedules
	void refreshSchedules();


signals:
	//! Is emitted when is the update of schedules needed
	void changed();
	
	
private:
	Database *_db;

};

#endif // SCHEDULER_H
