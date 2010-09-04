/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Aug 28 23:12:46 2010
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
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabTimer;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxTimer;
    QGridLayout *gridLayout;
    QLabel *labelSeconds;
    QSpinBox *spinBoxSeconds;
    QSpinBox *spinBoxMinutes;
    QLabel *labelMinutes;
    QSpinBox *spinBoxHours;
    QLabel *labelHours;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTimerInfo;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QSpacerItem *verticalSpacer;
    QWidget *tabSchedules;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBoxSchedules;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QDateTimeEdit *dateTimeEditEndDateTime;
    QLineEdit *titleLineEdit;
    QPushButton *pushButtonAdd;
    QPlainTextEdit *plainTextEditSchedule;
    QSpacerItem *verticalSpacer_2;
    Scheduler *scheduler;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonRemove;
    QMenuBar *menuBar;
    QMenu *menu_Main;
    QMenu *menu_Help;

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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabTimer = new QWidget();
        tabTimer->setObjectName(QString::fromUtf8("tabTimer"));
        verticalLayout = new QVBoxLayout(tabTimer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxTimer = new QGroupBox(tabTimer);
        groupBoxTimer->setObjectName(QString::fromUtf8("groupBoxTimer"));
        gridLayout = new QGridLayout(groupBoxTimer);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelSeconds = new QLabel(groupBoxTimer);
        labelSeconds->setObjectName(QString::fromUtf8("labelSeconds"));

        gridLayout->addWidget(labelSeconds, 0, 0, 1, 1);

        spinBoxSeconds = new QSpinBox(groupBoxTimer);
        spinBoxSeconds->setObjectName(QString::fromUtf8("spinBoxSeconds"));
        spinBoxSeconds->setMinimum(0);
        spinBoxSeconds->setMaximum(1000);
        spinBoxSeconds->setValue(0);

        gridLayout->addWidget(spinBoxSeconds, 0, 1, 1, 1);

        spinBoxMinutes = new QSpinBox(groupBoxTimer);
        spinBoxMinutes->setObjectName(QString::fromUtf8("spinBoxMinutes"));
        spinBoxMinutes->setMaximum(1000);

        gridLayout->addWidget(spinBoxMinutes, 0, 3, 1, 1);

        labelMinutes = new QLabel(groupBoxTimer);
        labelMinutes->setObjectName(QString::fromUtf8("labelMinutes"));

        gridLayout->addWidget(labelMinutes, 0, 2, 1, 1);

        spinBoxHours = new QSpinBox(groupBoxTimer);
        spinBoxHours->setObjectName(QString::fromUtf8("spinBoxHours"));
        spinBoxHours->setMaximum(100);

        gridLayout->addWidget(spinBoxHours, 0, 5, 1, 1);

        labelHours = new QLabel(groupBoxTimer);
        labelHours->setObjectName(QString::fromUtf8("labelHours"));

        gridLayout->addWidget(labelHours, 0, 4, 1, 1);


        verticalLayout->addWidget(groupBoxTimer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelTimerInfo = new QLabel(tabTimer);
        labelTimerInfo->setObjectName(QString::fromUtf8("labelTimerInfo"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelTimerInfo->setFont(font);

        horizontalLayout_2->addWidget(labelTimerInfo);

        lcdNumber = new QLCDNumber(tabTimer);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        lcdNumber->setFont(font1);
        lcdNumber->setLayoutDirection(Qt::RightToLeft);
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setSegmentStyle(QLCDNumber::Outline);
        lcdNumber->setProperty("intValue", QVariant(0));

        horizontalLayout_2->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonStart = new QPushButton(tabTimer);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setEnabled(true);

        horizontalLayout->addWidget(pushButtonStart);

        pushButtonStop = new QPushButton(tabTimer);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setEnabled(false);

        horizontalLayout->addWidget(pushButtonStop);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tabTimer, QString());
        tabSchedules = new QWidget();
        tabSchedules->setObjectName(QString::fromUtf8("tabSchedules"));
        gridLayout_3 = new QGridLayout(tabSchedules);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBoxSchedules = new QGroupBox(tabSchedules);
        groupBoxSchedules->setObjectName(QString::fromUtf8("groupBoxSchedules"));
        gridLayout_2 = new QGridLayout(groupBoxSchedules);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        dateTimeEditEndDateTime = new QDateTimeEdit(groupBoxSchedules);
        dateTimeEditEndDateTime->setObjectName(QString::fromUtf8("dateTimeEditEndDateTime"));

        verticalLayout_3->addWidget(dateTimeEditEndDateTime);

        titleLineEdit = new QLineEdit(groupBoxSchedules);
        titleLineEdit->setObjectName(QString::fromUtf8("titleLineEdit"));

        verticalLayout_3->addWidget(titleLineEdit);

        pushButtonAdd = new QPushButton(groupBoxSchedules);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));

        verticalLayout_3->addWidget(pushButtonAdd);

        plainTextEditSchedule = new QPlainTextEdit(groupBoxSchedules);
        plainTextEditSchedule->setObjectName(QString::fromUtf8("plainTextEditSchedule"));

        verticalLayout_3->addWidget(plainTextEditSchedule);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        scheduler = new Scheduler(groupBoxSchedules);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        scheduler->setHeaderItem(__qtreewidgetitem);
        scheduler->setObjectName(QString::fromUtf8("scheduler"));
        scheduler->setColumnCount(3);
        scheduler->header()->setCascadingSectionResizes(false);

        verticalLayout_3->addWidget(scheduler);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonRemove = new QPushButton(groupBoxSchedules);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));

        horizontalLayout_4->addWidget(pushButtonRemove);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBoxSchedules, 0, 0, 1, 1);

        tabWidget->addTab(tabSchedules, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 369, 22));
        menu_Main = new QMenu(menuBar);
        menu_Main->setObjectName(QString::fromUtf8("menu_Main"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_Main->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Main->addAction(actionPreferences);
        menu_Main->addAction(actionQuit);
        menu_Help->addAction(actionReportBug);
        menu_Help->addSeparator();
        menu_Help->addAction(actionAboutQt);
        menu_Help->addAction(actionAboutThisApplication);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


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
        groupBoxTimer->setTitle(QApplication::translate("MainWindow", "Set timer ", 0, QApplication::UnicodeUTF8));
        labelSeconds->setText(QApplication::translate("MainWindow", "Seconds:", 0, QApplication::UnicodeUTF8));
        spinBoxSeconds->setSuffix(QApplication::translate("MainWindow", "s", 0, QApplication::UnicodeUTF8));
        spinBoxMinutes->setSuffix(QApplication::translate("MainWindow", "m", 0, QApplication::UnicodeUTF8));
        labelMinutes->setText(QApplication::translate("MainWindow", "Minutes:", 0, QApplication::UnicodeUTF8));
        spinBoxHours->setSuffix(QApplication::translate("MainWindow", "h", 0, QApplication::UnicodeUTF8));
        labelHours->setText(QApplication::translate("MainWindow", "Hours:", 0, QApplication::UnicodeUTF8));
        labelTimerInfo->setText(QApplication::translate("MainWindow", "Not started", 0, QApplication::UnicodeUTF8));
        pushButtonStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabTimer), QApplication::translate("MainWindow", "Timer", 0, QApplication::UnicodeUTF8));
        groupBoxSchedules->setTitle(QApplication::translate("MainWindow", "Set schedule", 0, QApplication::UnicodeUTF8));
        dateTimeEditEndDateTime->setDisplayFormat(QApplication::translate("MainWindow", "M/d/yy hh:mm", 0, QApplication::UnicodeUTF8));
        pushButtonAdd->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        pushButtonRemove->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSchedules), QApplication::translate("MainWindow", "Schedules", 0, QApplication::UnicodeUTF8));
        menu_Main->setTitle(QApplication::translate("MainWindow", "&Main", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
