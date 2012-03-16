#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include <qdebug.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputBox->setReadOnly(true);
    connect(ui->chatButton, SIGNAL(clicked()), this, SLOT(startChat()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::startChat()
{
    QString     ipadd, portnum, username;
    QByteArray  ip, port, uname;
    int         result = 1;

    if((ipadd = ui->IPBox->toPlainText()) == "")
    {
        emit(MainWindow::displayError(QString("You Must Enter the ChatServer IP Address")));
        return;
    }

    ip = ipadd.toLocal8Bit();

    if((username = ui->UnameBox->toPlainText()) == "")
    {
        emit(MainWindow::displayError(QString("You Must Enter a Username")));
        return;
    }

    uname = username.toLocal8Bit();

    if((portnum = ui->PortBox->toPlainText()) == "")
    {
        client = new Client::Client(ip.data(), uname.data());
    }

    else
    {
        port = portnum.toLocal8Bit();
        client = new Client::Client(ip.data(), atoi(port.data()), uname.data());
    }

    if((result = client->configPort()) < 0)
    {
        switch(result)
        {
        case -1:
            emit(MainWindow::displayError(QString("Unable to Create Socket")));
            break;
        case -2:
            emit(MainWindow::displayError(QString("Unknown Server Address")));
            break;
        }
        return;
    }

    if((result = client->connectToServer()) < 0)
    {
        emit(MainWindow::displayError(QString("Unable To Connect To Server")));
        return;
    }

    ui->textLabel->setText("connected");
    ui->imageLable->setPixmap(QPixmap("connected.jpg"));


}

void MainWindow::displayError(QString error)
{
    ui->imageLable->setPixmap(QPixmap("error.png"));
    ui->textLabel->setText(error);
    ui->imageLable->show();
    update();


}
