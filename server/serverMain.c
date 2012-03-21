/*-------------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    ServerMain.c - contains the main() function, which is the entry point for the Message Cue Server
--                          program, and the catcher() function, which is a cleanup function called when the SIGINT
--                          signal is received.
--
--	PROGRAM:	    TCP Chat Program	
--
--	FUNCTIONS:	
--                  int main(void)
--                  
--	DATE:		    March 8, 2012			
--
--	REVISIONS:			
--
--	DESIGNERS:	    Mike Zobac
--                  Chris Sim		
--
--	PROGRAMMERS:    Mike Zobac
--                  Chris Sim   		
--
--	NOTES:          
--------------------------------------------------------------------------------------------------------------------------*/

#include "includes.h"
#include "server.h"
#include "wrappers.h"

/*-----------------------------------------------------------------------------------------------------------------------------
--		FUNCTION:	Main - The entry point for the Message Cueue Server program.  	
--
--		DATE:	    March 10, 2012		
--
--		DESIGNER:	Chris Sim
--
--		PROGRAMMER: Chris Sim		
--
--		INTERFACE:  int main(int argc, char *argv[])		
--
--		RETURNS:	int
--
--		NOTES:			
----------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	int i, arg, listen_sd, port;
	socklen_t client_len;
	struct sockaddr_in server;
   	pthread_t thread_process;
	PGLOBALS p = (PGLOBALS) malloc(sizeof(GLOBALS));

	switch(argc)
	{
		case 1:
			port = SERVER_TCP_PORT;	/* Use the default port */
		break;
		case 2:
			port = atoi(argv[1]);	/* Get user specified port */
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

	/* Create a stream socket */
	if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		SystemFatal("Cannot Create Socket!");
	
	/* set SO_REUSEADDR so port can be resused imemediately after exit, i.e., after CTRL-c */
    arg = 1;
    if (setsockopt (listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
        SystemFatal("setsockopt");

	/* Bind an address to the socket */
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); /* Accept connections from any client */

	if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
		SystemFatal("bind error");
	
	/* Listen for connections */
	/* queue up to LISTENQ connect requests */
	listen(listen_sd, LISTENQ);

	p->maxfd = listen_sd;	/* initialize */
   	p->maxi	= -1;			/* index into client[] array */

	for (i = 0; i < FD_SETSIZE; i++)
    	p->client[i] = -1;             /* -1 indicates available entry */
 	FD_ZERO(&p->allset);
   	FD_SET(listen_sd, &p->allset);


	while (TRUE)
	{
   		p->rset = p->allset;   /* structure assignment */
		p->nready = select(p->maxfd + 1, &(p->rset), NULL, NULL, NULL);

  		if (FD_ISSET(listen_sd, &(p->rset))) /* new client connection */
  		{
			client_len = sizeof(p->client_addr);
			if ((p->new_sd = accept(listen_sd, (struct sockaddr *) &(p->client_addr), &client_len)) == -1)
				SystemFatal("accept error"); 
	
			printf(" Client Connected:  %s\n", inet_ntoa(p->client_addr.sin_addr));

			for (i = 0; i < FD_SETSIZE; i++)
				if (p->client[i] < 0)
				{
					p->addressbook[i] = p->client_addr;
					p->client[i] = p->new_sd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE)
		 	{
				printf ("Too many clients\n");
				exit(1);
			}

			FD_SET (p->new_sd, &p->allset);     /* add new descriptor to set */
			if (p->new_sd > p->maxfd)
				p->maxfd = p->new_sd;	/* for select */

			if (i > p->maxi)
				p->maxi = i;	/* new max index in client[] array */
			
			if (--(p->nready) <= 0)
				continue;	/* no more readable descriptors */
 		}

		pthread_create(&thread_process, NULL, client_process, p);
		
    }
	return(0);
}

