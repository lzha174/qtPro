/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *stateLabel;
    QPushButton *changeState;
    QPushButton *quickB;
    QPushButton *interruptButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stateLabel = new QLabel(centralWidget);
        stateLabel->setObjectName(QStringLiteral("stateLabel"));
        stateLabel->setGeometry(QRect(80, 40, 131, 41));
        changeState = new QPushButton(centralWidget);
        changeState->setObjectName(QStringLiteral("changeState"));
        changeState->setGeometry(QRect(50, 110, 75, 23));
        quickB = new QPushButton(centralWidget);
        quickB->setObjectName(QStringLiteral("quickB"));
        quickB->setGeometry(QRect(310, 20, 75, 23));
        interruptButton = new QPushButton(centralWidget);
        interruptButton->setObjectName(QStringLiteral("interruptButton"));
        interruptButton->setGeometry(QRect(160, 110, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        stateLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        changeState->setText(QApplication::translate("MainWindow", "Change State", 0));
        quickB->setText(QApplication::translate("MainWindow", "Quit", 0));
        interruptButton->setText(QApplication::translate("MainWindow", "Interreupt", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
