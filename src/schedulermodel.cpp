#include "schedulermodel.h"

SchedulerModel::SchedulerModel(const QStringList &headers, QObject *parent) : QAbstractItemModel(parent) {
	
	QVector<QVariant> data;
	
	foreach (QString header, headers)
		data << header;
	
	_item = new Schedule(data);
}


SchedulerModel::~SchedulerModel() {
	
	delete _item;
}


QVariant SchedulerModel::data(const QModelIndex &index, int role) const {
	
	if (!index.isValid())
		return QVariant();
	
//! \todo zvolit spravne role..
	if (role != Qt::DisplayRole && role != Qt::EditRole)
         return QVariant();
	
	
	Schedule* item = getItem(index);
	
	return item->data(index.column());
}


int SchedulerModel::columnCount(const QModelIndex &/*parent = QModelIndex()*/) const {
	
	return _item->columnCount();
}


int SchedulerModel::rowCount(const QModelIndex &parent) const {
	
	Schedule* item = getItem(parent);
	
	//return item;
	return item->rowCount();
}


Schedule *SchedulerModel::getItem(const QModelIndex &index) const {
    
	if (index.isValid()) {
		Schedule *item = static_cast<Schedule*>(index.internalPointer());
		
		if (item)
			return item;
	}

	return _item;
}


QModelIndex SchedulerModel::parent(const QModelIndex &child) const {
	
	if (!child.isValid())
		return QModelIndex();
	
	Schedule* childItem = getItem(child);
	Schedule* parentItem = childItem->parent();
	
	if (parentItem == _item)
		return QModelIndex();
	
	QModelIndex i = createIndex(0, 0, parentItem);
	
	return i;
}


QModelIndex SchedulerModel::index(int row, int column, const QModelIndex &parent) const {
	
	if (parent.isValid() && parent.column() != 0)
			 return QModelIndex();
	
	Schedule* parentItem = getItem(parent);
	Schedule* childItem = NULL;//parentItem->child(row);
	
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();
}
