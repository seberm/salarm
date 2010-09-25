#ifndef SCHEDULERMODEL_H
#define SCHEDULERMODEL_H

#include "schedule.h"

#include <QAbstractItemModel>
#include <QModelIndex>

class SchedulerModel : public QAbstractItemModel {

Q_OBJECT

public:
	//! Constructor
	/*!
	  \param parent parent object
	*/
    explicit SchedulerModel(const QStringList &headers, QObject *parent = 0);
	
	//! Destructor
	~SchedulerModel();
	
	QVariant data(const QModelIndex &index, int role) const;
	Schedule* getItem(const QModelIndex &index) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

private:
	Schedule* _item;
	
signals:

public slots:

};

#endif // SCHEDULERMODEL_H
