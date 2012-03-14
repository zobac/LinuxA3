/*--------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    Client Main - 
--
--	PROGRAM:        TCP Chat Program		
--
--	FUNCTIONS:		
--                  
--	DATE:			March 8, 2012	
--
--	REVISIONS:			
--
--	DESIGNERS:		Mike Zobac
--                  Chris Sim	
--
--	PROGRAMMERS:	Mike Zobac
--                  Chris Sim	
--
--	NOTES:          
-------------------------------------------------------------------------------------------------------------------*/

#include "includes.h"
#include "client.h"
#include "wrappers.h"

static void SystemFatal(const char* message);

/*------------------------------------------------------------------------------------------------------------------

-- FUNCTION:    Main - the entry point for the Message Queue Client program.
--
-- DATE:        March 8, 2012
--
-- REVISIONS:    
--
-- DESIGNER:    Mike Zobac
--              Chris Sim 
--
-- PROGRAMMER:  Mike Zobac
--              Chris Sim 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- NOTES:       
-------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{

	int					clSocket, port, bytes_to_read;
	struct sockaddr_in 	server;
	struct hostent		*hp;
	char 				**pptr, *host, *str, *bp, rbuf[BUFLEN];
   	pthread_t       	inputThread;
   	size_t 	i;
   	
   	
   	
   	/*	Get the server port and IP */
   	
   	switch(argc)
	{
		case 2:
			host =	argv[1];			/* Host name  */
			port =	SERVER_TCP_PORT;
		break;
		case 3:
			host =	argv[1];
			port =	atoi(argv[2]);	/* User specified port  */
		break;
		default:
			fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
			exit(1);
	}
	
   	
   	/* Set up the Socket */
   	
   	if ((clSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		SystemFatal("Cannot Create Socket");
	}
	memset((char *)&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		SystemFatal("Unknown Server Address");
	}
	memcpy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	
	
	/* Connecting to the server  */
	
	if (connect (clSocket, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		SystemFatal("Cannot Connect to Server");
	}
	printf("Connected:    Server Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("\t\tIP Address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));
	
	
	/* get user data and sent it to server */
	pthread_create(&inputThread, NULL, sendText, &clSocket);
	
	/* read messages from the socket and print them */
	while(1)
	{
	
		bp = rbuf;
		bytes_to_read = BUFLEN;
	
		i = 0;
		while ((i = recv (clSocket, bp, bytes_to_read, 0)) < BUFLEN)
		{
			bp += i;
			bytes_to_read -= i;
		}
	
		printf ("%s\n", rbuf);
		fflush(stdout);
	}
	
	return(EXIT_SUCCESS);
}

static void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}


