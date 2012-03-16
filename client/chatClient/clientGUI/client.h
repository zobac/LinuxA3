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

#define BUFLEN              1024
#define BUFFSIZE            256
#define SERVER_TCP_PORT     4981


class Client
{
public:
    Client();
    Client(char * host, char * uname);
    Client(char * host, const int port, char * uname);
    ~Client();
    void sendText(const QString msg);
    QString receiveText();
    int configPort();
    int connectToServer();
    QString getServerName();
    QString getServerIP();

private:
    int                 clSocket_, port_;
    char                *host_, *uname_, rbuf_[BUFLEN];
    struct hostent      *hp_;
    struct sockaddr_in  server_;





};

#endif // CLIENT_H
