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

OptionsDialog::OptionsDialog(QSettings *settings, QWidget *parent) : QDialog(parent), m_ui(new Ui::OptionsDialog) {
	
    m_ui->setupUi(this);
	m_settings = settings;
	
	m_settings->beginGroup("App");
		m_ui->checkBoxCanClose->setChecked(!(m_settings->value("CanClose", false).toBool()));
		m_ui->comboBox->setCurrentIndex(m_settings->value("DatabaseDriver", 0).toInt());
	m_settings->endGroup();
	
	m_settings->beginGroup("MySQL");
		m_ui->lineEditMySQLHostname->setText(m_settings->value("HostName", "localhost").toString());
		m_ui->lineEditMySQLUsername->setText(m_settings->value("UserName", QString()).toString());
		m_ui->lineEditMySQLPassword->setText(m_settings->value("Password", QString()).toString());
		m_ui->lineEditMySQLDatabase->setText(m_settings->value("Database", "salarm").toString());
	m_settings->endGroup();
	
	m_dbChanged = false;
}


OptionsDialog::~OptionsDialog() {
	
    delete m_ui;
}


void OptionsDialog::changeEvent(QEvent *e) {
	
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void OptionsDialog::on_buttonBox_accepted() {
	
	if (m_dbChanged) {
		
		QMessageBox::information(this, tr("Database changed"), tr("The changes of database will take effect after the application restart."));
	}
	
	m_settings->beginGroup("MySQL");
		m_settings->setValue("HostName", m_ui->lineEditMySQLHostname->text());
		m_settings->setValue("UserName", m_ui->lineEditMySQLUsername->text());
		m_settings->setValue("Password", m_ui->lineEditMySQLPassword->text());
		m_settings->setValue("Database", m_ui->lineEditMySQLDatabase->text());
	m_settings->endGroup();
	
	m_settings->beginGroup("App");
		m_settings->setValue("DatabaseDriver", m_ui->comboBox->currentIndex());
		m_settings->setValue("CanClose", !(m_ui->checkBoxCanClose->isChecked()));
	m_settings->endGroup();
	
	close();
}


void OptionsDialog::on_comboBox_currentIndexChanged(QString index) {
	
    if (index == "MySQL")
		m_ui->groupBoxMySQL->setEnabled(true);
	else m_ui->groupBoxMySQL->setDisabled(true);
	
	m_dbChanged = true;
}
