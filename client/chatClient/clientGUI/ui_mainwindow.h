/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *portGroup;
    QTextEdit *PortBox;
    QGroupBox *ipGroup;
    QTextEdit *IPBox;
    QGroupBox *userGroup;
    QTextEdit *UnameBox;
    QGroupBox *outputGroup;
    QTextEdit *outputBox;
    QGroupBox *inputGroup;
    QTextEdit *inputBox;
    QPushButton *chatButton;
    QLabel *imageLable;
    QLabel *textLabel;
    QCheckBox *saveBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(663, 571);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        portGroup = new QGroupBox(centralWidget);
        portGroup->setObjectName(QString::fromUtf8("portGroup"));
        portGroup->setGeometry(QRect(10, 10, 151, 61));
        PortBox = new QTextEdit(portGroup);
        PortBox->setObjectName(QString::fromUtf8("PortBox"));
        PortBox->setGeometry(QRect(0, 20, 151, 21));
        ipGroup = new QGroupBox(centralWidget);
        ipGroup->setObjectName(QString::fromUtf8("ipGroup"));
        ipGroup->setGeometry(QRect(10, 60, 151, 41));
        IPBox = new QTextEdit(ipGroup);
        IPBox->setObjectName(QString::fromUtf8("IPBox"));
        IPBox->setGeometry(QRect(0, 20, 141, 31));
        userGroup = new QGroupBox(centralWidget);
        userGroup->setObjectName(QString::fromUtf8("userGroup"));
        userGroup->setGeometry(QRect(10, 110, 141, 41));
        UnameBox = new QTextEdit(userGroup);
        UnameBox->setObjectName(QString::fromUtf8("UnameBox"));
        UnameBox->setGeometry(QRect(0, 20, 141, 31));
        outputGroup = new QGroupBox(centralWidget);
        outputGroup->setObjectName(QString::fromUtf8("outputGroup"));
        outputGroup->setGeometry(QRect(330, 10, 321, 431));
        outputBox = new QTextEdit(outputGroup);
        outputBox->setObjectName(QString::fromUtf8("outputBox"));
        outputBox->setGeometry(QRect(0, 20, 311, 421));
        inputGroup = new QGroupBox(centralWidget);
        inputGroup->setObjectName(QString::fromUtf8("inputGroup"));
        inputGroup->setGeometry(QRect(10, 450, 651, 81));
        inputBox = new QTextEdit(inputGroup);
        inputBox->setObjectName(QString::fromUtf8("inputBox"));
        inputBox->setGeometry(QRect(0, 20, 641, 61));
        chatButton = new QPushButton(centralWidget);
        chatButton->setObjectName(QString::fromUtf8("chatButton"));
        chatButton->setGeometry(QRect(20, 190, 93, 27));
        imageLable = new QLabel(centralWidget);
        imageLable->setObjectName(QString::fromUtf8("imageLable"));
        imageLable->setGeometry(QRect(10, 260, 301, 181));
        textLabel = new QLabel(centralWidget);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));
        textLabel->setGeometry(QRect(10, 240, 311, 21));
        saveBox = new QCheckBox(centralWidget);
        saveBox->setObjectName(QString::fromUtf8("saveBox"));
        saveBox->setGeometry(QRect(10, 160, 101, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 663, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        portGroup->setTitle(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        ipGroup->setTitle(QApplication::translate("MainWindow", "Server IP:", 0, QApplication::UnicodeUTF8));
        userGroup->setTitle(QApplication::translate("MainWindow", "User Name:", 0, QApplication::UnicodeUTF8));
        outputGroup->setTitle(QApplication::translate("MainWindow", "Output", 0, QApplication::UnicodeUTF8));
        inputGroup->setTitle(QApplication::translate("MainWindow", "Input", 0, QApplication::UnicodeUTF8));
        chatButton->setText(QApplication::translate("MainWindow", "Chat!", 0, QApplication::UnicodeUTF8));
        imageLable->setText(QString());
        textLabel->setText(QString());
        saveBox->setText(QApplication::translate("MainWindow", "Save Chat?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
