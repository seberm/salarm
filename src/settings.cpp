
#include <settings.h>
#include <constants.h>
#include <QtDebug>

QSettings* g_settings = 0;


void initSettings() {
	
	g_settings = new QSettings(CONFIG_FILE, QSettings::IniFormat);
}



//! \todo dodelat ukonceni v main!
void exitSettings() {
	
	delete g_settings;
}
