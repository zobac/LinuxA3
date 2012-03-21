#ifndef READTHREAD_H
#define READTHREAD_H

#include <QThread>
#include <QString>
#include "client.h"


class ReadThread : public QThread
{
Q_OBJECT
public:
    explicit ReadThread(QObject *parent = 0, Client *client = 0);
    void run();

signals:
    void messageReceived(QString);

public slots:

private:
    Client *client_;

};

#endif // READTHREAD_H
