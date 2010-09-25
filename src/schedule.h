#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QList>
#include <QVector>
#include <QVariant>

class Schedule {
	
public:
    /*explicit */Schedule(const QVector<QVariant> &data, Schedule* parent = 0);
	~Schedule();
				 
	Schedule* child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	Schedule* parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
	
private:
	QList<Schedule*> _childItems;
	QVector<QVariant> _itemData;
	Schedule* _parentItem;
	
};

#endif // SCHEDULE_H
