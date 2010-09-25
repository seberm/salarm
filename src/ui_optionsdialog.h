/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created: Sat Sep 25 22:45:57 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QGridLayout *gridLayout;
    QToolBox *toolBox;
    QWidget *pageApp;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxCanClose;
    QHBoxLayout *horizontalLayout_2;
    QWidget *pageDatabase;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxMySQL;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEditMySQLUsername;
    QLabel *labelMySQLUsername;
    QLabel *labelMySQLDatabase;
    QLabel *labelMySQLHostname;
    QLabel *labelMySQLPassword;
    QLineEdit *lineEditMySQLPassword;
    QLineEdit *lineEditMySQLDatabase;
    QLineEdit *lineEditMySQLHostname;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QString::fromUtf8("OptionsDialog"));
        OptionsDialog->setWindowModality(Qt::NonModal);
        OptionsDialog->resize(320, 240);
        gridLayout = new QGridLayout(OptionsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolBox = new QToolBox(OptionsDialog);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        pageApp = new QWidget();
        pageApp->setObjectName(QString::fromUtf8("pageApp"));
        pageApp->setGeometry(QRect(0, 0, 121, 47));
        gridLayout_3 = new QGridLayout(pageApp);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxCanClose = new QCheckBox(pageApp);
        checkBoxCanClose->setObjectName(QString::fromUtf8("checkBoxCanClose"));
        checkBoxCanClose->setChecked(true);

        horizontalLayout->addWidget(checkBoxCanClose);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        toolBox->addItem(pageApp, QString::fromUtf8("Application settings"));
        pageDatabase = new QWidget();
        pageDatabase->setObjectName(QString::fromUtf8("pageDatabase"));
        pageDatabase->setGeometry(QRect(0, 0, 302, 133));
        gridLayout_2 = new QGridLayout(pageDatabase);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBoxMySQL = new QGroupBox(pageDatabase);
        groupBoxMySQL->setObjectName(QString::fromUtf8("groupBoxMySQL"));
        groupBoxMySQL->setEnabled(false);
        gridLayout_4 = new QGridLayout(groupBoxMySQL);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lineEditMySQLUsername = new QLineEdit(groupBoxMySQL);
        lineEditMySQLUsername->setObjectName(QString::fromUtf8("lineEditMySQLUsername"));

        gridLayout_4->addWidget(lineEditMySQLUsername, 3, 1, 1, 1);

        labelMySQLUsername = new QLabel(groupBoxMySQL);
        labelMySQLUsername->setObjectName(QString::fromUtf8("labelMySQLUsername"));

        gridLayout_4->addWidget(labelMySQLUsername, 3, 0, 1, 1);

        labelMySQLDatabase = new QLabel(groupBoxMySQL);
        labelMySQLDatabase->setObjectName(QString::fromUtf8("labelMySQLDatabase"));

        gridLayout_4->addWidget(labelMySQLDatabase, 3, 2, 1, 1);

        labelMySQLHostname = new QLabel(groupBoxMySQL);
        labelMySQLHostname->setObjectName(QString::fromUtf8("labelMySQLHostname"));

        gridLayout_4->addWidget(labelMySQLHostname, 1, 0, 1, 1);

        labelMySQLPassword = new QLabel(groupBoxMySQL);
        labelMySQLPassword->setObjectName(QString::fromUtf8("labelMySQLPassword"));

        gridLayout_4->addWidget(labelMySQLPassword, 1, 2, 1, 1);

        lineEditMySQLPassword = new QLineEdit(groupBoxMySQL);
        lineEditMySQLPassword->setObjectName(QString::fromUtf8("lineEditMySQLPassword"));
        lineEditMySQLPassword->setEchoMode(QLineEdit::Password);

        gridLayout_4->addWidget(lineEditMySQLPassword, 1, 3, 1, 1);

        lineEditMySQLDatabase = new QLineEdit(groupBoxMySQL);
        lineEditMySQLDatabase->setObjectName(QString::fromUtf8("lineEditMySQLDatabase"));

        gridLayout_4->addWidget(lineEditMySQLDatabase, 3, 3, 1, 1);

        lineEditMySQLHostname = new QLineEdit(groupBoxMySQL);
        lineEditMySQLHostname->setObjectName(QString::fromUtf8("lineEditMySQLHostname"));

        gridLayout_4->addWidget(lineEditMySQLHostname, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBoxMySQL, 1, 0, 1, 1);

        comboBox = new QComboBox(pageDatabase);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 0, 1, 1);

        toolBox->addItem(pageDatabase, QString::fromUtf8("Database"));

        gridLayout->addWidget(toolBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        checkBoxCanClose->setText(QApplication::translate("OptionsDialog", "To tray if closed", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(pageApp), QApplication::translate("OptionsDialog", "Application settings", 0, QApplication::UnicodeUTF8));
        groupBoxMySQL->setTitle(QApplication::translate("OptionsDialog", "MySQL configuration", 0, QApplication::UnicodeUTF8));
        labelMySQLUsername->setText(QApplication::translate("OptionsDialog", "Username:", 0, QApplication::UnicodeUTF8));
        labelMySQLDatabase->setText(QApplication::translate("OptionsDialog", "Database:", 0, QApplication::UnicodeUTF8));
        labelMySQLHostname->setText(QApplication::translate("OptionsDialog", "Hostname", 0, QApplication::UnicodeUTF8));
        labelMySQLPassword->setText(QApplication::translate("OptionsDialog", "Password:", 0, QApplication::UnicodeUTF8));
        lineEditMySQLPassword->setText(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("OptionsDialog", "SQLite", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OptionsDialog", "MySQL", 0, QApplication::UnicodeUTF8)
        );
        toolBox->setItemText(toolBox->indexOf(pageDatabase), QApplication::translate("OptionsDialog", "Database", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
