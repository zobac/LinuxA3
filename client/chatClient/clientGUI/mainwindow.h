#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startChat();
    void displayError(QString error);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow  *ui;
    Client::Client  *client;


};

#endif // MAINWINDOW_H
