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


#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"


namespace Ui {
	
    class OptionsDialog;
}


//! Provides preferences dialog
class OptionsDialog : public QDialog {
	
    Q_OBJECT
	
	public:
	
		//! Constructor
		/*!
		  \param parent pointer to parent object
		*/
		OptionsDialog(QWidget *parent = 0);
		
		//! Destructor
		~OptionsDialog();
	
	protected:
		
		//! When language is changed the window is retranslated
		void changeEvent(QEvent *e);
	
	private:
		
		//! Pointer to Option dialog's UI
		Ui::OptionsDialog *m_ui;
	
	private slots:
		
		//! Is called whenever database structure is changed
		void databaseChanged(int);
		
		//! Is called when dialog is accepted
		void dialogAccepted();
		
		//! Opens the color dialog and sets color of expired schedule in scheduler
		void setExpiredScheduleColor();
		
		//! Opens the file dialog and inserts choosen sound into combo box
		void addAlarmSound();
	
};

#endif // OPTIONSDIALOG_H
