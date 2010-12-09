#include "schedulerproxymodel.h"
#include "scheduler.h"


SchedulerProxyModel::SchedulerProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
	
	setFilterRole(Qt::EditRole);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
	setDynamicSortFilter(true);
}


bool SchedulerProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {

	extern const int columnCount;
	for (int col = 0; col < columnCount; col++) {
		
		QModelIndex index = sourceModel()->index(sourceRow, col, sourceParent);
		
		if (sourceModel()->data(index).toString().contains(filterRegExp()))
			return true;
		
	}
	
	return false;
}
