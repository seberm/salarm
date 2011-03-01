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


#ifndef KEYCATCHER_H
#define KEYCATCHER_H

#include <QObject>


class KeyCatcher : public QObject {
	
    Q_OBJECT
	
public:
	
	/*! Constructor
	  \param parent pointer to parent object
	*/
    explicit KeyCatcher(QObject *parent = 0);

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	
signals:
	//! Is emmited when the some key is pressed
	void keyPressed(int key);

};

#endif // KEYCATCHER_H
