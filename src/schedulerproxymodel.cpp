#include "schedulerproxymodel.h"

SchedulerProxyModel::SchedulerProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
	
	setFilterRole(Qt::EditRole);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
	setDynamicSortFilter(true);
}


bool SchedulerProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {

	for (int col = 1; col <= 3; col++) {
		QModelIndex index = sourceModel()->index(sourceRow, col, sourceParent);
		
		if (sourceModel()->data(index).toString().contains(filterRegExp()))
			return true;
		
	}
	
	return false;
}
