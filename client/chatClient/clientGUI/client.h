#ifndef CLIENT_H
#define CLIENT_H


#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <qstring.h>
#include <stdio.h>

#define BUFLEN              1024
#define BUFFSIZE            256
#define SERVER_TCP_PORT     4981


class Client
{
public:
    Client();
    Client(char * host, QString uname);
    Client(char * host, const int port, QString uname);
    ~Client();
    void sendText(const QString msg);
    QString receiveText();
    int configPort();
    int connectToServer();
    QString getServerName();
    QString getServerIP();
    void closeSocket();
    void setSave(bool value);
    void saveChat(QString message);


private:
    int                 clSocket_, port_;
    char                *host_, rbuf_[BUFLEN];
    QString             uname_;
    struct hostent      *hp_;
    struct sockaddr_in  server_;
    bool                saveFile_;
    FILE                *logFile_;





};

#endif // CLIENT_H
