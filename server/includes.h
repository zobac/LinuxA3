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



typedef struct _globals
{
    int     port;
    
}GLOBALS, *PGLOBALS;

#endif
