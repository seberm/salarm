/*
 * sAlarm - Scheduler
 * http://salarm.seberm.com
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


#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

#include "scheduledialog.h"
#include "ui_scheduledialog.h"
#include "database.h"
#include "scheduler.h"

extern const Column DBID;
extern const Column CategoryID;
extern const Column Status;
extern const Column Title;
extern const Column Text;
extern const Column Expiration;
extern const Column Category;


ScheduleDialog::ScheduleDialog(Database *sqlDb, Scheduler *scheduler, QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
	m_sqlDb = sqlDb;
	m_scheduler = scheduler;
    ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Add;
	
	initialize();
	
	makeConnections();
	
	m_scheduleID = 0;
}


ScheduleDialog::ScheduleDialog(Database *sqlDb, Scheduler *scheduler, const QModelIndex &index, QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
	m_sqlDb = sqlDb;
	m_scheduler = scheduler;
	ui->setupUi(this);
	
	dialogAction = ScheduleDialog::Edit;
	
	initialize();
	
	makeConnections();
	
	m_scheduleID = index.sibling(index.row(), DBID.columnID).data().toInt();
	int categoryID = index.sibling(index.row(), CategoryID.columnID).data().toInt();

	QString title = index.sibling(index.row(), Title.columnID).data().toString();
	QString text = index.sibling(index.row(), Text.columnID).data().toString();
	
	QDateTime expirationDateTime = index.sibling(index.row(), Expiration.columnID).data().toDateTime();
	QDate expirationDate = expirationDateTime.date();
	
	ui->lineEditTitle->setText(title);
	ui->plainTextEditText->setPlainText(text);
	ui->dateTimeEditExpiration->setDateTime(expirationDateTime);
	ui->calendar->setSelectedDate(expirationDate);
	
	if (categoryID <= 0)
		categoryID = 0;
		
	ui->comboBoxCategory->setCurrentIndex(ui->comboBoxCategory->findData(categoryID));
}


void ScheduleDialog::initialize() {
	
	// Add schedule categories to combo box
	// Default category
	ui->comboBoxCategory->addItem(tr("No category"), 0);
	
	QSqlQuery query(m_sqlDb->sqlDb());
	
	QString sql = "SELECT id, name FROM ScheduleCategory;";
	query.exec(sql);
	while (query.next())
		ui->comboBoxCategory->addItem(query.value(1).toString(), query.value(0).toInt());
	
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

	switch (dialogAction)	{
		
		default:
		case ScheduleDialog::Add:
		
			m_scheduler->addSchedule(ui->lineEditTitle->text(),
			                         ui->plainTextEditText->toPlainText(),
			                         ui->dateTimeEditExpiration->dateTime(),
			                         ui->comboBoxCategory->itemData(ui->comboBoxCategory->currentIndex()).toInt());
			break;
			
		case ScheduleDialog::Edit:
		
			m_scheduler->editSchedule(m_scheduleID,
									 ui->lineEditTitle->text(),
									 ui->plainTextEditText->toPlainText(),
									 ui->dateTimeEditExpiration->dateTime(),
									 ui->comboBoxCategory->itemData(ui->comboBoxCategory->currentIndex()).toInt());
			break;
	}

	//emit (changed());
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
		
		QString sql = "INSERT INTO ScheduleCategory (name)" \
					  "VALUES (:name);";
		
		QSqlQuery query(m_sqlDb->sqlDb());
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
	
	QString sql = "DELETE FROM ScheduleCategory" \
				  " WHERE id = :id;";

	QSqlQuery query(m_sqlDb->sqlDb());
	query.prepare(sql);
	query.addBindValue(id);
	
	if (!query.exec()) {
		
		qWarning() << query.lastError();
		return;
	}
	
	ui->comboBoxCategory->removeItem(index);
}
