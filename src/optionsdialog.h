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


#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QMessageBox>


namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog {
    Q_OBJECT
	
	public:
		OptionsDialog(QWidget *parent = 0);
		~OptionsDialog();
	
	signals:
		
	protected:
		void changeEvent(QEvent *e);
	
	private:
		Ui::OptionsDialog *m_ui;
		
		bool m_dbChanged;
	
	private slots:
		void databaseChanged(QString);
		void dialogAccepted();
		
		//! Opens the color dialog and sets color of expired schedule in scheduler
		void setExpiredScheduleColor();
		
		//! Opens the file dialog and inserts choosen sound into combo box
		void addAlarmSound();
	
};

#endif // OPTIONSDIALOG_H
