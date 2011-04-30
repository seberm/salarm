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


#include <QFileDialog>
#include <QColorDialog>
#include <QtDebug>

#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "database.h"
#include "settings.h"
extern QSettings *g_settings;

// Has database changed during the configuring?
static bool dbChanged = false;

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), m_ui(new Ui::OptionsDialog) {
	
	// Setup UI
    m_ui->setupUi(this);
	
	m_ui->labelExpiredScheduleColor->setAutoFillBackground(true);
	
	// Adds combobox database items
	m_ui->comboBoxDatabases->addItem("SQLite", Database::SQLite);
	m_ui->comboBoxDatabases->addItem("MySQL", Database::MySQL);
	
	g_settings->beginGroup("App");
		m_ui->checkBoxCanClose->setChecked(!(g_settings->value("CanClose", false).toBool()));
		
		int currentDBDriver = g_settings->value("DatabaseDriver").toInt();
		if (m_ui->comboBoxDatabases->itemData(currentDBDriver).toInt() == Database::MySQL) {
			
			m_ui->groupBoxMySQL->setEnabled(true);
			m_ui->comboBoxDatabases->setCurrentIndex(currentDBDriver);
		}
		
		g_settings->beginGroup("Postpone");
			QTime time(g_settings->value("Hour").toInt(), g_settings->value("Minute").toInt(), g_settings->value("Second", 10).toInt());
			m_ui->timeEditPostpone->setTime(time);
		g_settings->endGroup();
	g_settings->endGroup();

	g_settings->beginGroup("MySQL");
		m_ui->lineEditMySQLHostname->setText(g_settings->value("HostName", "localhost").toString());
		m_ui->lineEditMySQLUsername->setText(g_settings->value("UserName").toString());
		m_ui->lineEditMySQLPassword->setText(g_settings->value("Password").toString());
		m_ui->lineEditMySQLDatabase->setText(g_settings->value("Database", "salarm").toString());
	g_settings->endGroup();

	g_settings->beginGroup("SMTP");
		m_ui->lineEditSMTPHostname->setText(g_settings->value("HostName").toString());
		m_ui->lineEditSMTPUsername->setText(g_settings->value("UserName").toString());
		m_ui->lineEditSMTPPassword->setText(g_settings->value("Password").toString());
	g_settings->endGroup();
	
	int size = g_settings->beginReadArray("Sounds");
		for (int i = 1; i < size; i++) {
			
			g_settings->setArrayIndex(i);
			QString filename = g_settings->value("sound").toString();
			
			QFileInfo f(filename);
			m_ui->comboBoxSounds->addItem(f.baseName(), f.absoluteFilePath());
		}
	g_settings->endArray();
	
	g_settings->beginGroup("GUI");
		QPalette palette = m_ui->labelExpiredScheduleColor->palette();
		palette.setColor(m_ui->labelExpiredScheduleColor->backgroundRole(), g_settings->value("ExpiredScheduleColor", Qt::white).value<QColor>());	
		m_ui->labelExpiredScheduleColor->setPalette(palette);
	g_settings->endGroup();
	
	g_settings->beginGroup("App");
		m_ui->sliderVolume->setSliderPosition(g_settings->value("AlarmVolume", 50).toInt());
	
		QFileInfo sound(g_settings->value("AlarmSound").toString());
		m_ui->comboBoxSounds->setCurrentIndex(m_ui->comboBoxSounds->findText(sound.baseName()));	
	g_settings->endGroup();
	
	
	// Dialog connections
	connect(m_ui->comboBoxDatabases, SIGNAL(currentIndexChanged(int)), this, SLOT(databaseChanged(int)));
	connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(dialogAccepted()));
	connect(m_ui->pushButtonSetExpiredScheduleColor, SIGNAL(pressed()), this, SLOT(setExpiredScheduleColor()));
	connect(m_ui->pushButtonOpenFile, SIGNAL(pressed()), this, SLOT(addAlarmSound()));
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
	
	if (dbChanged)
		QMessageBox::information(this, tr("Database changed"), tr("The changes of database will take effect after the application restart."));
	
	g_settings->beginGroup("MySQL");
		g_settings->setValue("HostName", m_ui->lineEditMySQLHostname->text());
		g_settings->setValue("UserName", m_ui->lineEditMySQLUsername->text());
		g_settings->setValue("Password", m_ui->lineEditMySQLPassword->text());
		g_settings->setValue("Database", m_ui->lineEditMySQLDatabase->text());
	g_settings->endGroup();
	
	g_settings->beginGroup("SMTP");
		g_settings->setValue("HostName", m_ui->lineEditSMTPHostname->text());
		g_settings->setValue("Password", m_ui->lineEditSMTPPassword->text());
		g_settings->setValue("UserName", m_ui->lineEditSMTPUsername->text());
	g_settings->endGroup();
		
	g_settings->beginGroup("App");
		g_settings->setValue("DatabaseDriver", m_ui->comboBoxDatabases->itemData(m_ui->comboBoxDatabases->currentIndex()));
		g_settings->setValue("CanClose", !(m_ui->checkBoxCanClose->isChecked()));
		g_settings->setValue("AlarmSound", m_ui->comboBoxSounds->itemData(m_ui->comboBoxSounds->currentIndex()));
		g_settings->setValue("AlarmVolume", m_ui->sliderVolume->value());
		g_settings->beginGroup("Postpone");
			g_settings->setValue("Hour", m_ui->timeEditPostpone->time().hour());
			g_settings->setValue("Minute", m_ui->timeEditPostpone->time().minute());
			g_settings->setValue("Second", m_ui->timeEditPostpone->time().second());
		g_settings->endGroup();
	g_settings->endGroup();
	
	g_settings->beginGroup("GUI");
		g_settings->setValue("ExpiredScheduleColor", m_ui->labelExpiredScheduleColor->palette().color(m_ui->labelExpiredScheduleColor->backgroundRole()));
	g_settings->endGroup();
	
	close();
}


void OptionsDialog::databaseChanged(int itemIndex) {

	if (itemIndex == -1)
		return;
	
	int itemData = m_ui->comboBoxDatabases->itemData(itemIndex).toInt();
	switch (itemData) {
		
		case Database::MySQL:
			qDebug() << "changed database to: MySQL";
			m_ui->groupBoxMySQL->setEnabled(true);
			dbChanged = true;
			break;
		case Database::SQLite:
			qDebug() << "changed database to: SQLite";
			m_ui->groupBoxMySQL->setDisabled(true);
			dbChanged = true;
			break;
		
		default:
			qWarning() << "bad database id: " << itemData;
			break;
	}
}


void OptionsDialog::addAlarmSound() {

	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open sound"),
													QDir::homePath(),
													tr("Supported files") + "(*.mp3 *.mp4 *.wav *.3gp *.ogg);; " + tr("All files") + " (*.*)");
	
	
	if (filename.isEmpty())
		return;
	
	int size = m_ui->comboBoxSounds->count();
	
	g_settings->beginWriteArray("Sounds");
				
		QFileInfo f(filename);
		m_ui->comboBoxSounds->addItem(f.baseName(), f.absoluteFilePath());
				
		g_settings->setArrayIndex(size + 1);
		g_settings->setValue("sound", f.absoluteFilePath());
				
	g_settings->endArray();
}


void OptionsDialog::setExpiredScheduleColor() {
	
	QColor color = QColorDialog::getColor(g_settings->value("ExpiredScheduleColor").value<QColor>(), this, tr("Expired schedule background"));
	
	{
		QPalette palette = m_ui->labelExpiredScheduleColor->palette();
		palette.setColor(m_ui->labelExpiredScheduleColor->backgroundRole(), color);	
		m_ui->labelExpiredScheduleColor->setPalette(palette);
	}
}
