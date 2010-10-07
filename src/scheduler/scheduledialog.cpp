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

#include "scheduledialog.h"
#include "ui_scheduledialog.h"


ScheduleDialog::ScheduleDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ScheduleDialog) {
	
    ui->setupUi(this);
	
	// Add schedule categories to combo box
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	
	QString sql = "SELECT id, name FROM ScheduleCategory;";
	query.exec(sql);
	while (query.next())
		ui->comboBoxCategory->addItem(query.value(1).toString(), query.value(0));
	
	
	ui->dateTimeEditExpiration->setDateTime(QDateTime::currentDateTime());
	
	makeConnections();
}


ScheduleDialog::ScheduleDialog(const QString &title, const QString &text, const QDateTime &expiration, QWidget *parent) : QDialog(parent) {
	
	// Call the explicit constructor because of creation of object connections
	ScheduleDialog();
	
	ui->lblTitle->setText(title);
	ui->plainTextEditText->setPlainText(text);
	ui->dateTimeEditExpiration->setDateTime(expiration);
}


ScheduleDialog::~ScheduleDialog() {
	
    delete ui;
}


void ScheduleDialog::makeConnections() {
	
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(scheduleAccepted()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
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


void ScheduleDialog::addSchedule() {

	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QSqlQuery query(sqlConnection);
	query.prepare("INSERT INTO Schedule (title, text, datetime, categoryID)" \
				  "VALUES(:title, :text, :datetime, :categoryID)");
	
	query.bindValue(0, ui->lineEditTitle->text().simplified());
	query.bindValue(1, ui->plainTextEditText->toPlainText().simplified());
	query.bindValue(2, ui->dateTimeEditExpiration->dateTime());
	query.bindValue(3, ui->comboBoxCategory->itemData(ui->comboBoxCategory->currentIndex()));
	
	
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
	
	addSchedule();
	
	close();
}



