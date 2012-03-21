#include "readthread.h"

ReadThread::ReadThread(QObject *parent, Client *client) :
    QThread(parent), client_(client)
{
}

void ReadThread::run()
{
    QString result;

    while (1)
    {
        result = client_->receiveText();
        emit  messageReceived(result);
    }
}
