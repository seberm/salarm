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


#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
    class ScheduleDialog;
}

class ScheduleDialog : public QDialog {
    Q_OBJECT
public:
	explicit ScheduleDialog(QWidget *parent = 0);
	ScheduleDialog(const QString &title, const QString &text, const QDateTime &expiration, QWidget *parent = 0);
    ~ScheduleDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ScheduleDialog *ui;
	
	void addSchedule();
	void makeConnections();
	
signals:
	//! Is emitted when is the update of schedules needed
	void changed();
	
private slots:
	void scheduleAccepted();
	
};

#endif // SCHEDULEDIALOG_H
