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


#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QSettings *settings, QWidget *parent) : QDialog(parent), _ui(new Ui::OptionsDialog) {
	
    _ui->setupUi(this);
	_settings = settings;
	
	_settings->beginGroup("App");
		_ui->checkBoxCanClose->setChecked(!(_settings->value("CanClose", false).toBool()));
		_ui->comboBox->setCurrentIndex(_settings->value("DatabaseDriver", 0).toInt());
	_settings->endGroup();
	
	_settings->beginGroup("MySQL");
		_ui->lineEditMySQLHostname->setText(_settings->value("HostName", "localhost").toString());
		_ui->lineEditMySQLUsername->setText(_settings->value("UserName", QString()).toString());
		_ui->lineEditMySQLPassword->setText(_settings->value("Password", QString()).toString());
		_ui->lineEditMySQLDatabase->setText(_settings->value("Database", "salarm").toString());
	_settings->endGroup();
	
	_dbChanged = false;
}


OptionsDialog::~OptionsDialog() {
	
    delete _ui;
}


void OptionsDialog::changeEvent(QEvent *e) {
	
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        _ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void OptionsDialog::on_buttonBox_accepted() {
	
	if (_dbChanged) {
		
		QMessageBox::information(this, tr("Database changed"), tr("The changes of database will take effect after the application restart."));
	}
	
	_settings->beginGroup("MySQL");
		_settings->setValue("HostName", _ui->lineEditMySQLHostname->text());
		_settings->setValue("UserName", _ui->lineEditMySQLUsername->text());
		_settings->setValue("Password", _ui->lineEditMySQLPassword->text());
		_settings->setValue("Database", _ui->lineEditMySQLDatabase->text());
	_settings->endGroup();
	
	_settings->beginGroup("App");
		_settings->setValue("DatabaseDriver", _ui->comboBox->currentIndex());
		_settings->setValue("CanClose", !(_ui->checkBoxCanClose->isChecked()));
	_settings->endGroup();
	
	close();
}


void OptionsDialog::on_comboBox_currentIndexChanged(QString index) {
	
    if (index == "MySQL")
		_ui->groupBoxMySQL->setEnabled(true);
	else _ui->groupBoxMySQL->setDisabled(true);
	
	_dbChanged = true;
}
