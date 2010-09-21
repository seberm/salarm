#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>

namespace Ui {
    class ScheduleDialog;
}

class ScheduleDialog : public QDialog {
    Q_OBJECT
public:
    ScheduleDialog(QWidget *parent = 0);
    ~ScheduleDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ScheduleDialog *ui;
};

#endif // SCHEDULEDIALOG_H
