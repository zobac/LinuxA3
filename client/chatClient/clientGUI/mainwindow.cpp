/*---------------------------------------------------------------------------------------------------------
SOURCE FILE:
--
-- PROGRAM:
--
-- Methods:
--          int main(void) - the driver for the program.
--
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Mike Zobac
--
-- PROGRAMMER: Mike Zobac
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readthread.h"
#include <qdebug.h>


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputBox->installEventFilter(this);
    ui->outputBox->setReadOnly(true);
    saveFile = false;
    connected = false;
    connect(ui->chatButton, SIGNAL(clicked()), this, SLOT(startChat()));
    connect(this, SIGNAL(enterPressed()), this, SLOT(sendData()));
}


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

MainWindow::~MainWindow()
{
    client->closeSocket();
    delete ui;
}


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

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


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

void MainWindow::startChat()
{
    QString     ipadd, portnum;
    QByteArray  ip, port, uname;
    int         result = 1;


    if(!connected)
    {

        connected = true;
        if(ui->saveBox->isChecked())
        {
            saveFile = true;
        }
        if((ipadd = ui->IPBox->toPlainText()) == "")
        {
            emit(MainWindow::displayError(QString("You Must Enter the ChatServer IP Address")));
            return;
        }

        ip = ipadd.toLocal8Bit();

        if((username_ = ui->UnameBox->toPlainText()) == "")
        {
            emit(MainWindow::displayError(QString("You Must Enter a Username")));
            return;
        }

        if((portnum = ui->PortBox->toPlainText()) == "")
        {
            client = new Client(ip.data(), username_);
            if(ui->saveBox->isChecked())
            {
                client->setSave(true);
            }
        }

        else
        {
            port = portnum.toLocal8Bit();
            client = new Client(ip.data(), atoi(port.data()), username_);
            if(ui->saveBox->isChecked())
            {
                client->setSave(true);
            }
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
        read =  new ReadThread(this, client);
        connect(read, SIGNAL(messageReceived(QString)), this, SLOT(displayMessage(QString)));
        read->start();
    }

    else
    {
        emit(MainWindow::displayError(QString("Already Connected to Server!")));
        sleep(2000);
        ui->textLabel->setText("connected");
        ui->imageLable->setPixmap(QPixmap("connected.jpg"));
    }
}


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

void MainWindow::displayError(QString error)
{
    ui->imageLable->setPixmap(QPixmap("error.png"));
    ui->textLabel->setText(error);
    ui->imageLable->show();
    update();
}


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

void MainWindow::displayMessage(QString message)
{
    ui->outputBox->append(message);
}


/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

void MainWindow::sendData()
{
    QString data = username_;
    data.append(": ");
    data.append(ui->inputBox->toPlainText());
    ui->outputBox->append(data);
    client->sendText(data);
    ui->inputBox->clear();
}



/*----------------------------------------------------------------------------------------------------------
-- METHOD:
--
-- DATE:        March 13, 2012
--
-- REVISIONS:   (Date and Description)
--
-- DESIGNER:    Mike Zobac
--
-- PROGRAMMER:  Mike Zobac
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
----------------------------------------------------------------------------------------------------------*/

bool MainWindow::eventFilter(QObject* obj,QEvent* event)
{
    if(obj == ui->inputBox)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            {
                //The user has hit enter or return
                emit enterPressed();
                return true;
            }
            else
            {
                 //let the window pass it on to be handled
                return QMainWindow::eventFilter(obj,event);
            }
        }
    }
    return QMainWindow::eventFilter(obj,event);
}
