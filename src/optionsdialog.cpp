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

#include <QFileDialog>
#include <QtDebug>


OptionsDialog::OptionsDialog(QSettings *settings, QWidget *parent) : QDialog(parent), m_ui(new Ui::OptionsDialog) {
	
    m_ui->setupUi(this);
	m_settings = settings;
	
	m_settings->beginGroup("App");
		m_ui->checkBoxCanClose->setChecked(!(m_settings->value("CanClose", false).toBool()));
		m_ui->comboBoxDatabases->setCurrentIndex(m_settings->value("DatabaseDriver", 0).toInt());

//! \todo findData nepracuje spravne...proc?, zacalo zlobit vyhazovani hlasky o zmene Db..pritom zadna nebyla..	
m_ui->comboBoxSounds->setCurrentIndex(m_ui->comboBoxSounds->findText(m_settings->value("AlarmSound").toString()));
qDebug() << m_ui->comboBoxSounds->findText(m_settings->value("AlarmSound").toString());

	m_settings->endGroup();

	m_settings->beginGroup("MySQL");
		m_ui->lineEditMySQLHostname->setText(m_settings->value("HostName", "localhost").toString());
		m_ui->lineEditMySQLUsername->setText(m_settings->value("UserName", QString()).toString());
		m_ui->lineEditMySQLPassword->setText(m_settings->value("Password", QString()).toString());
		m_ui->lineEditMySQLDatabase->setText(m_settings->value("Database", "salarm").toString());
	m_settings->endGroup();
	
	int size = m_settings->beginReadArray("Sounds");
		for (int i = 0; i < size; i++) {
			
			m_settings->setArrayIndex(i);
			QString filename = m_settings->value("sound").toString();
			
			QFileInfo f(filename);
			m_ui->comboBoxSounds->addItem(f.fileName(), f.absoluteFilePath());
		}
	m_settings->endArray();
	
	m_dbChanged = false;
	
	connect(m_ui->pushButtonOpenFile, SIGNAL(pressed()), this, SLOT(addAlarmSound()));
	connect(m_ui->comboBoxDatabases, SIGNAL(currentIndexChanged(QString)), this, SLOT(databaseChanged(QString)));
	connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(dialogAccepted()));
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


void OptionsDialog::dialogAccepted() {
	
	if (m_dbChanged)
		QMessageBox::information(this, tr("Database changed"), tr("The changes of database will take effect after the application restart."));
	
	m_settings->beginGroup("MySQL");
		m_settings->setValue("HostName", m_ui->lineEditMySQLHostname->text());
		m_settings->setValue("UserName", m_ui->lineEditMySQLUsername->text());
		m_settings->setValue("Password", m_ui->lineEditMySQLPassword->text());
		m_settings->setValue("Database", m_ui->lineEditMySQLDatabase->text());
	m_settings->endGroup();
	
	m_settings->beginGroup("App");
		m_settings->setValue("DatabaseDriver", m_ui->comboBoxDatabases->currentIndex());
		m_settings->setValue("CanClose", !(m_ui->checkBoxCanClose->isChecked()));
		m_settings->setValue("AlarmSound", m_ui->comboBoxSounds->itemData(m_ui->comboBoxSounds->currentIndex()));
	m_settings->endGroup();
	
	close();
}


void OptionsDialog::databaseChanged(QString index) {
	
    if (index == "MySQL")
		m_ui->groupBoxMySQL->setEnabled(true);
	else m_ui->groupBoxMySQL->setDisabled(true);
	
	m_dbChanged = true;
}


void OptionsDialog::addAlarmSound() {

	QStringList filenames = QFileDialog::getOpenFileNames(this,
													tr("Open sound"),
													QDir::homePath(),
													tr("Supported files") + "(*.mp3 *.mp4 *.wav *.3gp *.ogg);; " + tr("All files") + " (*.*)");
	
	
	if (filenames.isEmpty())
		return;
	
	int size = m_ui->comboBoxSounds->count();
	
	m_settings->beginWriteArray("Sounds");
		for (int i = size; i < filenames.size(); i++) {
				
			QFileInfo f(filenames.at(i));
			m_ui->comboBoxSounds->addItem(f.fileName());
				
			m_settings->setArrayIndex(i);
			m_settings->setValue("sound", f.absoluteFilePath());
				
		}
	m_settings->endArray();
}


