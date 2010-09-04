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


#include "timer.h"


Timer::Timer(int sec, int min, int hour) {
	_finalMSeconds = 0;
	
	setTime(sec, min, hour);
}


void Timer::startApp() {
	start(_finalMSeconds);
}


void Timer::stopApp() {
	stop();
}


void Timer::setTime(int sec, int min, int hour) {
	_finalMSeconds = 0;
	_seconds = sec;
	_minutes = min;
	_hours = hour;
	
	if (_seconds > 0)
		_finalMSeconds += _seconds * 1000;
	
	if (_minutes > 0)
		_finalMSeconds += _minutes * 60 * 1000;
	
	if (_hours > 0)
		_finalMSeconds += _hours * 60 * 60 * 1000;
	
}
