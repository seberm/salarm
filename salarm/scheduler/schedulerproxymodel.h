#ifndef SCHEDULERPROXYMODEL_H
#define SCHEDULERPROXYMODEL_H

#include <QSortFilterProxyModel>


class SchedulerProxyModel : public QSortFilterProxyModel {
	
Q_OBJECT

public:
    explicit SchedulerProxyModel(QObject *parent = 0);
	
protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;


};

#endif // SCHEDULERPROXYMODEL_H
