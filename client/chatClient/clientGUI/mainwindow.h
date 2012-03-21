#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QString>
#include "client.h"
#include "readthread.h"
#include "QKeyEvent"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void enterPressed();


public slots:
    void startChat();
    void displayError(QString error);
    void displayMessage(QString message);
    void sendData();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::MainWindow          *ui;
    Client                  *client;
    bool                    saveFile, connected;
    ReadThread              *read;
    QString                 username_;


};

#endif // MAINWINDOW_H
