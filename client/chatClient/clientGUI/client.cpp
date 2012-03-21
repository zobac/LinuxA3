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

#include "client.h"


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

Client::Client()
{
    port_ = SERVER_TCP_PORT;
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

Client::Client(char * host, QString uname)
    : host_(host), uname_(uname)
{
    port_ = SERVER_TCP_PORT;
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

Client::Client(char * host, const int port, QString uname)
    :port_(port), host_(host), uname_(uname)
{
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

Client::~Client()
{
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

void Client::sendText(const QString msg)
{

    const char *mesg;
    ssize_t ret;

    mesg = msg.toStdString().c_str();

    if ((ret = send(clSocket_, mesg, strlen(mesg), 0)) == -1)
        perror("send");

    printf("%d\n", ret);
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

QString Client::receiveText()
{
    int     bytesToRead;
    char    *bp;
    ssize_t bytesRead;
    QString *result;

    bp = Client::rbuf_;
    bytesToRead = BUFLEN;

    bytesRead = recv(Client::clSocket_, bp, bytesToRead, 0);
    if (bytesRead == -1)
        perror("recv");

    bp[bytesRead] = '\0';

    result = new QString(rbuf_);
    return(*result);
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

int Client::connectToServer()
{
    if (connect (Client::clSocket_, (struct sockaddr *)&(Client::server_), sizeof(Client::server_)) == -1)
    {
        return(-1);
    }
    return(0);
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

QString Client::getServerName()
{
    QString *result;
    result = new QString(Client::hp_->h_name);
    return(*result);
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

QString Client::getServerIP()
{
    char **pptr, *str;
    QString *result;

    pptr = hp_->h_addr_list;
    result = new QString((char*)inet_ntop(Client::hp_->h_addrtype, *pptr, str, sizeof(str)));
    return(*result);
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

void Client::closeSocket()
{
    shutdown(clSocket_, SHUT_RDWR);
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

void Client::setSave(bool value)
{
    saveFile_ = value;
}
