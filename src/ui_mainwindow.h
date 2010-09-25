/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Sep 25 12:07:41 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "scheduler.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionReportBug;
    QAction *actionAboutQt;
    QAction *actionAboutThisApplication;
    QAction *actionPreferences;
    QAction *actionNewSchedule;
    QAction *actionScheduleEdit;
    QAction *actionScheduleRemove;
    QAction *actionOpenSchedulesList;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    Scheduler *scheduler;
    QMenuBar *menuBar;
    QMenu *menu_Main;
    QMenu *menu_Help;
    QMenu *menuSchedule;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(369, 444);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/alarmIcon"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/closeIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon1);
        actionReportBug = new QAction(MainWindow);
        actionReportBug->setObjectName(QString::fromUtf8("actionReportBug"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/bugIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionReportBug->setIcon(icon2);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/qtIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutQt->setIcon(icon3);
        actionAboutThisApplication = new QAction(MainWindow);
        actionAboutThisApplication->setObjectName(QString::fromUtf8("actionAboutThisApplication"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/infoIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutThisApplication->setIcon(icon4);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/optionsIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon5);
        actionNewSchedule = new QAction(MainWindow);
        actionNewSchedule->setObjectName(QString::fromUtf8("actionNewSchedule"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/loadIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewSchedule->setIcon(icon6);
        actionScheduleEdit = new QAction(MainWindow);
        actionScheduleEdit->setObjectName(QString::fromUtf8("actionScheduleEdit"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/editIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionScheduleEdit->setIcon(icon7);
        actionScheduleRemove = new QAction(MainWindow);
        actionScheduleRemove->setObjectName(QString::fromUtf8("actionScheduleRemove"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/deleteIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionScheduleRemove->setIcon(icon8);
        actionOpenSchedulesList = new QAction(MainWindow);
        actionOpenSchedulesList->setObjectName(QString::fromUtf8("actionOpenSchedulesList"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/openIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenSchedulesList->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scheduler = new Scheduler(centralWidget);
        scheduler->setObjectName(QString::fromUtf8("scheduler"));

        verticalLayout_2->addWidget(scheduler);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 369, 22));
        menu_Main = new QMenu(menuBar);
        menu_Main->setObjectName(QString::fromUtf8("menu_Main"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menuSchedule = new QMenu(menuBar);
        menuSchedule->setObjectName(QString::fromUtf8("menuSchedule"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_Main->menuAction());
        menuBar->addAction(menuSchedule->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Main->addAction(actionNewSchedule);
        menu_Main->addAction(actionPreferences);
        menu_Main->addAction(actionQuit);
        menu_Help->addAction(actionReportBug);
        menu_Help->addSeparator();
        menu_Help->addAction(actionAboutQt);
        menu_Help->addAction(actionAboutThisApplication);
        menuSchedule->addAction(actionOpenSchedulesList);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "sAlarm Scheduler", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionReportBug->setText(QApplication::translate("MainWindow", "&Report bug", 0, QApplication::UnicodeUTF8));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About &Qt", 0, QApplication::UnicodeUTF8));
        actionAboutThisApplication->setText(QApplication::translate("MainWindow", "About this application", 0, QApplication::UnicodeUTF8));
        actionPreferences->setText(QApplication::translate("MainWindow", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionPreferences->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionNewSchedule->setText(QApplication::translate("MainWindow", "&New schedule", 0, QApplication::UnicodeUTF8));
        actionNewSchedule->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionScheduleEdit->setText(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        actionScheduleRemove->setText(QApplication::translate("MainWindow", "&Remove", 0, QApplication::UnicodeUTF8));
        actionOpenSchedulesList->setText(QApplication::translate("MainWindow", "&Open schedules list", 0, QApplication::UnicodeUTF8));
        menu_Main->setTitle(QApplication::translate("MainWindow", "&Main", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuSchedule->setTitle(QApplication::translate("MainWindow", "&Schedules", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
