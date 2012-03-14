#ifndef SERVER_H
#define SERVER_H

#define SERVER_TCP_PORT 4981
#define BUFLEN	80	
#define TRUE	1
#define LISTENQ	5
#define MAXLINE 4096

void* client_setup();
void* client_process();

#endif
