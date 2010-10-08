/*
 * sAlarm - Scheduler
 * http://seberm.homelinux.org/project/salarm
 *
 * Copyright (C) 2009-2010 Otto Sabart <seberm[at]gmail[dot]com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QDebug>

#include <QMessageBox>
#include <QSqlDriver>

#include "scheduledialog.h"
#include "ui_scheduledialog.h"


ScheduleDialog::ScheduleDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
    ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Add;
	
	initialize();
	
	makeConnections();
}


ScheduleDialog::ScheduleDialog(const QModelIndex &index, QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
	ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Edit;
	
	initialize();
	
	makeConnections();
	
	_scheduleID = index.sibling(index.row(), 0).data().toInt();

	QString title = index.sibling(index.row(), 1).data().toString();
	QString text = index.sibling(index.row(), 2).data().toString();
	QDateTime expirationDateTime = index.sibling(index.row(), 3).data().toDateTime();
	QDate expirationDate = index.sibling(index.row(), 3).data().toDate();
	int categoryID = index.sibling(index.row(), 5).data().toInt();
	
	ui->lineEditTitle->setText(title);
	ui->plainTextEditText->setPlainText(text);
	ui->dateTimeEditExpiration->setDateTime(expirationDateTime);
	ui->calendar->setSelectedDate(expirationDate);
	ui->comboBoxCategory->setCurrentIndex(categoryID);
}


void ScheduleDialog::initialize() {
	
	// Add schedule categories to combo box
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	
	QString sql = "SELECT id, name FROM ScheduleCategory;";
	query.exec(sql);
	while (query.next())
		ui->comboBoxCategory->addItem(query.value(1).toString(), query.value(0));
	
	
	ui->dateTimeEditExpiration->setDateTime(QDateTime::currentDateTime());
	ui->calendar->setSelectedDate(QDate::currentDate());
}


ScheduleDialog::~ScheduleDialog() {
	
    delete ui;
}


void ScheduleDialog::makeConnections() {
	
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(scheduleAccepted()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	
	connect(ui->calendar, SIGNAL(clicked(QDate)), ui->dateTimeEditExpiration, SLOT(setDate(QDate)));
	connect(ui->dateTimeEditExpiration, SIGNAL(dateChanged(QDate)), ui->calendar, SLOT(setSelectedDate(QDate)));
}


void ScheduleDialog::changeEvent(QEvent *e) {
	
    QDialog::changeEvent(e);
    switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
			
		default:
			break;
    }
}


void ScheduleDialog::doSchedule() {

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	
	QString sql;
	
	switch (dialogAction)	{
		default:
		case ScheduleDialog::Add:
			sql = "INSERT INTO Schedule (title, text, datetime, categoryID)" \
				  " VALUES(:title, :text, :datetime, :categoryID)";
			
			break;
			
		case ScheduleDialog::Edit:
			
			sql = "UPDATE Schedule SET title = :title, text = :text, datetime = :datetime, categoryID = :categoryID" \
				  " WHERE id = ?;";
			
		
			
			break;
	}

	query.prepare(sql);
	
	query.bindValue(0, ui->lineEditTitle->text().simplified());
	query.bindValue(1, ui->plainTextEditText->toPlainText().simplified());
	query.bindValue(2, ui->dateTimeEditExpiration->dateTime());
	query.bindValue(3, ui->comboBoxCategory->itemData(ui->comboBoxCategory->currentIndex()).toInt());
	
	if(dialogAction == ScheduleDialog::Edit)
		query.bindValue(4, _scheduleID);
	
	if (!query.exec())
		qDebug() << query.lastError();

	emit (changed());
}


void ScheduleDialog::scheduleAccepted() {
	
	QString str = ui->lineEditTitle->text();
	
	if (str.isEmpty()) {
		QMessageBox::warning(this, tr("Fill the title"), tr("You must fill the title."));
		return;
	}
	
	doSchedule();
	
	close();
}

