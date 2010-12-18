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


#ifndef TIMEOUTDIALOG_H
#define TIMEOUTDIALOG_H


#include <QDialog>
#include <QDateTime>
#include <QCloseEvent>


namespace Ui {
	
    class TimeoutDialog;
}

namespace Phonon {
	
	class MediaObject;
	//class MediaSource;
	//class AudioOutput;
}

using namespace Phonon;


class TimeoutDialog : public QDialog {
    
	Q_OBJECT

public:
	//! Constructor
    explicit TimeoutDialog(int scheduleID, QWidget *parent = 0);
	
	//! Desctructor
    ~TimeoutDialog();
	
	
protected:
	//! Implemented because of stopping the phonon player
	void closeEvent(QCloseEvent* e);	

	
private:
	//! Connects all needed objects
	void makeConnections();
	
	//! Shows information about schedule
	void inform();
	
    Ui::TimeoutDialog *ui;
	
	//! Keeps a schedule database ID
	int m_scheduleID;
	
	//! Keeps the schedule text
	QString m_text;
	
	//! Here is a schedule title
	QString m_title;
	
	//! Datetime information about schedule timeout
	QDateTime m_expiration;
	
	//! It plays schedule timeout sound
	MediaObject *m_player;

	
signals:
	
	void postponed(int);
	void confirmed(int);
	
	
private slots:
	
	void confirm();
	void postpone();
	
};

#endif // TIMEOUTDIALOG_H
