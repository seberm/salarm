/*
 * sAlarm - Scheduler
 * http://seberm.homelinux.org/salarm
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


#ifndef TIMER_H
#define TIMER_H


#include <QTimer>
//#include <QThread>


//! Timer class
/*!
	Timer provides interface for sAlarm's Time module
*/
class Timer : public QTimer {
	Q_OBJECT
	
	public:
		//Timer(QObject *parent = 0);
		//! Constructor
		/*!
			Inicializes the timer
			\param parent pointer to parent object
		*/
		Timer (int sec = 0, int min = 0, int hour = 0);
		
		//! Starts the timer counting
		void startApp();
		
		//! Stops the timer
		void stopApp();
		
		//! Sets the time to timer
		void setTime (int sec, int min, int hour);
	
	private:
		//! Seconds
		int _seconds;
		
		//! Minutes
		int _minutes;
		
		//! Hours
		int _hours;
		
		//! Total count of seconds
		int _finalMSeconds;
	
};

#endif // TIMER_H
