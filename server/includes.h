#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

typedef struct _globals
{
    struct sockaddr_in client_addr, addressbook[FD_SETSIZE];
    fd_set rset, allset;
    int maxi, new_sd, maxfd, client[FD_SETSIZE], nready;
    
}GLOBALS, *PGLOBALS;

#endif
