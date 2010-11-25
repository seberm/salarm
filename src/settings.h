#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

//! Global settings variable
extern QSettings *g_settings;

//! Creates the QSettings instance
void initSettings();

void exitSettings();


#endif // SETTINGS_H
