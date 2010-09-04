#include "schedule.h"


/*Schedule::Schedule(int rowID, const QString &title, const QString &text, QDateTime expiration) {
	
	_rowID = rowID;
	_title = title;
	_text = text;
	_expiration = expiration;
	
	
	setText(0, _title);
	setText(1, _text);
	setText(2, _expiration.toString());
}
*/

/*Schedule::Schedule(QTreeWidgetItem *parent) : QTreeWidgetItem(parent) {
	
}*/


int Schedule::dbID () {
	
	return _rowID;
}
