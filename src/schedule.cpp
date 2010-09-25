#include "schedule.h"

Schedule::Schedule(const QVector<QVariant> &data, Schedule* parent) {

	if (data.isEmpty()) {
		itemData.fill(QString(),8);
	} else {
		itemData = data;
	}
	
	_parent = parent;
}


int Schedule::childCount() const {
	
    return childItems.size();
}


Schedule* Schedule::parent() {
	
     return _parent;
}


Schedule* Schedule::child(int number) { 
	
    if (number > childItems.size())
        return 0;

    return childItems.value(number);
}
