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


#include "scheduledialog.h"
#include "ui_scheduledialog.h"



#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>


ScheduleDialog::ScheduleDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
    ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Add;
	
	initialize();
	
	makeConnections();
	
	m_scheduleID = 0;
}


ScheduleDialog::ScheduleDialog(const QModelIndex &index, QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
	ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Edit;
	
	initialize();
	
	makeConnections();
	
//! \todo The number of columns must be defined in some constants or structures (scheduler.cpp)
	m_scheduleID = index.sibling(index.row(), 0).data().toInt();
	int categoryID = index.sibling(index.row(), 1).data().toInt();
	
	QString title = index.sibling(index.row(), 3).data().toString();
	QString text = index.sibling(index.row(), 4).data().toString();
	QDateTime expirationDateTime = index.sibling(index.row(), 5).data().toDateTime();
	QDate expirationDate = index.sibling(index.row(), 6).data().toDate();
	
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
	ui->dateTimeEditExpiration->setMinimumDateTime(QDateTime::currentDateTime());
	
	ui->calendar->setSelectedDate(QDate::currentDate());
	ui->calendar->setMinimumDate(QDate::currentDate());
}


ScheduleDialog::~ScheduleDialog() {
	
    delete ui;
}


void ScheduleDialog::makeConnections() {
	
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(scheduleAccepted()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	
	connect(ui->calendar, SIGNAL(clicked(QDate)), ui->dateTimeEditExpiration, SLOT(setDate(QDate)));
	connect(ui->dateTimeEditExpiration, SIGNAL(dateChanged(QDate)), ui->calendar, SLOT(setSelectedDate(QDate)));
	
	connect(ui->pushButtonAddCategory, SIGNAL(pressed()), this, SLOT(addCategory()));
	connect(ui->pushButtonRemoveCategory, SIGNAL(pressed()), this, SLOT(removeCategory()));
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
			
			sql = "UPDATE Schedule SET title = :title, text = :text, datetime = :datetime, categoryID = :categoryID, timeouted = 0" \
				  " WHERE id = ?;";
			
			break;
	}

	query.prepare(sql);
	
	query.bindValue(0, ui->lineEditTitle->text().simplified());
	query.bindValue(1, ui->plainTextEditText->toPlainText().simplified());
	query.bindValue(2, ui->dateTimeEditExpiration->dateTime());
	query.bindValue(3, ui->comboBoxCategory->itemData(ui->comboBoxCategory->currentIndex()).toInt());
	
	if(dialogAction == ScheduleDialog::Edit)
		query.bindValue(4, m_scheduleID);
	
	if (!query.exec())
		qWarning() << query.lastError();

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


void ScheduleDialog::addCategory() {
	
	bool ok;
	QString category = QInputDialog::getText(this, tr("Category name"), tr("Insert the category name:"),QLineEdit::Normal, tr("Category"), &ok);
	
	if (ok && !category.isEmpty()) {
		
		QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
		
		QString sql = "INSERT INTO ScheduleCategory (name)" \
					  "VALUES (:name);";
		
		QSqlQuery query(sqlConnection);
		query.prepare(sql);
		query.addBindValue(category);
		
		if (!query.exec()) {
			qWarning() << query.lastError();
			return;
		}
		
		int insertID = query.lastInsertId().toInt();

		ui->comboBoxCategory->addItem(category, insertID);
		ui->comboBoxCategory->setCurrentIndex(ui->comboBoxCategory->count() - 1);
	}
}


void ScheduleDialog::removeCategory() {
	
	int index = ui->comboBoxCategory->currentIndex();
	int id = ui->comboBoxCategory->itemData(index).toInt();
	
	// We cannot remove the default category
	if (index == 0)
		return;
	
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	
	QString sql = "DELETE FROM ScheduleCategory" \
				  " WHERE id = :id;";

	QSqlQuery query(sqlConnection);
	query.prepare(sql);
	query.addBindValue(id);
	
	if (!query.exec()) {
		qWarning() << query.lastError();
		return;
	}
	
	ui->comboBoxCategory->removeItem(index);
}
