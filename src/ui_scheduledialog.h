/********************************************************************************
** Form generated from reading UI file 'scheduledialog.ui'
**
** Created: Sat Sep 25 22:45:57 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEDIALOG_H
#define UI_SCHEDULEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScheduleDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEditText;
    QLabel *lblText;
    QDateTimeEdit *dateTimeEditExpiration;
    QLabel *lblExpiration;
    QLineEdit *lineEditTitle;
    QLabel *lblTitle;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ScheduleDialog)
    {
        if (ScheduleDialog->objectName().isEmpty())
            ScheduleDialog->setObjectName(QString::fromUtf8("ScheduleDialog"));
        ScheduleDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ScheduleDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plainTextEditText = new QPlainTextEdit(ScheduleDialog);
        plainTextEditText->setObjectName(QString::fromUtf8("plainTextEditText"));

        gridLayout->addWidget(plainTextEditText, 1, 1, 1, 1);

        lblText = new QLabel(ScheduleDialog);
        lblText->setObjectName(QString::fromUtf8("lblText"));

        gridLayout->addWidget(lblText, 1, 0, 1, 1);

        dateTimeEditExpiration = new QDateTimeEdit(ScheduleDialog);
        dateTimeEditExpiration->setObjectName(QString::fromUtf8("dateTimeEditExpiration"));

        gridLayout->addWidget(dateTimeEditExpiration, 2, 1, 1, 1);

        lblExpiration = new QLabel(ScheduleDialog);
        lblExpiration->setObjectName(QString::fromUtf8("lblExpiration"));

        gridLayout->addWidget(lblExpiration, 2, 0, 1, 1);

        lineEditTitle = new QLineEdit(ScheduleDialog);
        lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

        gridLayout->addWidget(lineEditTitle, 0, 1, 1, 1);

        lblTitle = new QLabel(ScheduleDialog);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));

        gridLayout->addWidget(lblTitle, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ScheduleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(lineEditTitle, plainTextEditText);
        QWidget::setTabOrder(plainTextEditText, dateTimeEditExpiration);
        QWidget::setTabOrder(dateTimeEditExpiration, buttonBox);

        retranslateUi(ScheduleDialog);

        QMetaObject::connectSlotsByName(ScheduleDialog);
    } // setupUi

    void retranslateUi(QDialog *ScheduleDialog)
    {
        ScheduleDialog->setWindowTitle(QApplication::translate("ScheduleDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lblText->setText(QApplication::translate("ScheduleDialog", "Text", 0, QApplication::UnicodeUTF8));
        lblExpiration->setText(QApplication::translate("ScheduleDialog", "Expiration", 0, QApplication::UnicodeUTF8));
        lblTitle->setText(QApplication::translate("ScheduleDialog", "Title:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScheduleDialog: public Ui_ScheduleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEDIALOG_H
