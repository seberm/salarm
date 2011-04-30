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
#include <QFileInfo>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/audiooutput.h>

#include "timeoutdialog.h"
#include "ui_timeoutdialog.h"
#include "settings.h"
extern QSettings *g_settings;


TimeoutDialog::TimeoutDialog(int scheduleID, QWidget *parent) : QDialog(parent), ui(new Ui::TimeoutDialog) {
	
    ui->setupUi(this);
	m_scheduleID = scheduleID;
	
	m_player = new MediaObject(this);
	AudioOutput *audioOutput = new AudioOutput(MusicCategory, this);
	Path path = Phonon::createPath(m_player, audioOutput);
	
	g_settings->beginGroup("App");
		audioOutput->setVolume(g_settings->value("AlarmVolume", 50).toReal() / 100);
	g_settings->endGroup();
	
	
	QSqlDatabase sqlConnection = QSqlDatabase::database("Schedules");
	QString sqlData = "SELECT title, text, datetime" \
					  " FROM Schedule" \
					  " WHERE id = ?;";
	
	QSqlQuery queryData(sqlConnection);
	
	queryData.prepare(sqlData);
	queryData.addBindValue(m_scheduleID);
	
	if (!queryData.exec()) {
		
		qWarning() << queryData.lastError();
		return;
	}
	
	while (queryData.next()) {
		
		m_title = queryData.value(0).toString();
		m_text = queryData.value(1).toString();
		m_expiration = queryData.value(2).toDateTime();
	}
	
	ui->labelTitle->setText(m_title);
	ui->labelDateTime->setText(m_expiration.toString());
	
	makeConnections();
	inform();
}


TimeoutDialog::~TimeoutDialog() {
	
    delete ui;
}


void TimeoutDialog::makeConnections() {
	
	connect(ui->pushButtonConfirm, SIGNAL(pressed()), this, SLOT(confirm()));
	connect(ui->pushButtonPostpone, SIGNAL(pressed()), this, SLOT(postpone()));
}


void TimeoutDialog::inform() {

	QFileInfo fi(g_settings->value("App/AlarmSound").toString());
	
	if (fi.exists()) {

		m_player->setCurrentSource(MediaSource(fi.absoluteFilePath()));
		m_player->play();
		
	} else
		qWarning() << tr("sound file for schedule warning does not exists");

}


void TimeoutDialog::confirm() {
	
	emit confirmed(m_scheduleID);
	close();
}


void TimeoutDialog::postpone() {
	
	emit postponed(m_scheduleID);
	close();
}


void TimeoutDialog::closeEvent(QCloseEvent *e) {
	
	if (m_player->state() == Phonon::PlayingState)
		m_player->stop();
	
	e->accept();
}
