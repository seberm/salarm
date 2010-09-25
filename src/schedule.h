#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QStandardItem>

class Schedule : public QStandardItem {
	
public:
    Schedule(const QVector<QVariant> &data, Schedule* parent = 0);
	
	int childCount() const;
	Schedule* child(int number);
	
	Schedule *parent();
	
private:
	QVector<QVariant> itemData;
	
	QList<Schedule*> childItems;
	Schedule *_parent;
};

#endif // SCHEDULE_H
