/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Sep 28 00:10:09 2010
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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionReportBug;
    QAction *actionAboutQt;
    QAction *actionAboutThisApplication;
    QAction *actionPreferences;
    QAction *actionNew;
    QAction *actionEdit;
    QAction *actionRemove;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menuBar;
    QMenu *menuMain;
    QMenu *menuHelp;
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
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/loadIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon6);
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QString::fromUtf8("actionEdit"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/editIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon7);
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/deleteIcon"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove->setIcon(icon8);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 369, 22));
        menuMain = new QMenu(menuBar);
        menuMain->setObjectName(QString::fromUtf8("menuMain"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuSchedule = new QMenu(menuBar);
        menuSchedule->setObjectName(QString::fromUtf8("menuSchedule"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMain->menuAction());
        menuBar->addAction(menuSchedule->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuMain->addAction(actionPreferences);
        menuMain->addAction(actionQuit);
        menuHelp->addAction(actionReportBug);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAboutQt);
        menuHelp->addAction(actionAboutThisApplication);
        menuSchedule->addAction(actionNew);
        menuSchedule->addSeparator();
        menuSchedule->addAction(actionEdit);
        menuSchedule->addAction(actionRemove);

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
        actionNew->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionEdit->setText(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        actionRemove->setText(QApplication::translate("MainWindow", "&Remove", 0, QApplication::UnicodeUTF8));
        menuMain->setTitle(QApplication::translate("MainWindow", "&Main", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuSchedule->setTitle(QApplication::translate("MainWindow", "&Schedule", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
