#include "client.h"

Client::Client()
{
    port_ = SERVER_TCP_PORT;
}

Client::Client(char * host, char * uname)
    : host_(host), uname_(uname)
{
    port_ = SERVER_TCP_PORT;
}

Client::Client(char * host, const int port, char * uname)
    :port_(port), host_(host), uname_(uname)
{
}

Client::~Client()
{
    delete(host_);
    delete(*uname_);
    delete(*hp_);
}

void Client::sendText(const QString msg)
{
    QByteArray  message;

    message = msg.toLocal8Bit();

    send(clSocket_, message.data(), BUFLEN, 0);
}

QString Client::receiveText()
{
    int     bytesToRead;
    char    *bp;
    size_t  i;
    QString *result;

    bp = Client::rbuf_;
    bytesToRead = BUFLEN;

    i = 0;
    while ((i = recv (Client::clSocket_, bp, bytesToRead, 0)) < BUFLEN)
    {
            bp += i;
            bytesToRead -= i;
    }
    result = new QString(rbuf_);
    return(*result);
}


int Client::configPort()
{
    if ((Client::clSocket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
            return(-1);
    }
    memset((char *)&(Client::server_), 0, sizeof(struct sockaddr_in));
    Client::server_.sin_family = AF_INET;
    Client::server_.sin_port = htons(port_);
    if ((hp_ = gethostbyname(host_)) == NULL)
    {
        return(-2);
    }
    memcpy(hp_->h_addr, (char *)&(Client::server_.sin_addr), hp_->h_length);
    return(0);
}

int Client::connectToServer()
{
    if (connect (Client::clSocket_, (struct sockaddr *)&(Client::server_), sizeof(Client::server_)) == -1)
    {
        return(-1);
    }
    return(0);
}

QString Client::getServerName()
{
    QString *result;
    result = new QString(Client::hp_->h_name);
    return(*result);
}

QString Client::getServerIP()
{
    char **pptr, *str;
    QString *result;

    pptr = hp_->h_addr_list;
    result = new QString((char*)inet_ntop(Client::hp_->h_addrtype, *pptr, str, sizeof(str)));
    return(*result);
}
