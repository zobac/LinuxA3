/*--------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    Server.c - 
--
--	PROGRAM:	    TCP Chat Program
--
--	FUNCTIONS:	
--                  
--	DATE:		    March 8, 2012		
--
--	REVISIONS:			
--
--	DESIGNERS:	    Mike Zobac
                    Chris Sim		
--
--	PROGRAMMERS:    Mike Zobac
--                  Chris Sim   		
--
--	NOTES:          
-----------------------------------------------------------------------------------------------------------------------*/

#include "includes.h"
#include "server.h"


/*------------------------------------------------------------------------------------------------------------------------
--	FUNCTION:	Client_process	
--
--	DATE:	    March 12, 2012	
--
--	DESIGNER:	Chris Sim
--
--	PROGRAMMER: Chris Sim
--
--	INTERFACE:  void* client_process(void* param)	
--
--	RETURNS:	void*
--
--	NOTES:		
---------------------------------------------------------------------------------------------------------------------------*/
void* client_process(void* param)
{
	char *dummy = "";
	int sockfd, n, i, k, bytes_to_read;
	char *bp, buf[BUFLEN], msg[BUFLEN];
	PGLOBALS p = (PGLOBALS) param; 
		
	for (i = 0; i <= p->maxi; i++)	/* check all clients for data */
 	{
		if ((sockfd = p->client[i]) < 0)
			continue;

		if (FD_ISSET(sockfd, &p->rset))
     	{
     		bp = buf;
			bytes_to_read = BUFLEN;
            n = read(sockfd, bp, bytes_to_read);
            if(n > 0)
            {
            	sprintf(msg, "%s: %s", inet_ntoa(p->addressbook[k].sin_addr), buf);
				write(2, msg, BUFLEN);
            }
            else if(n == 0 && p->client[i] != -1) /* connection closed by client */
            {
				printf(" Client disconnected:  %s\n", inet_ntoa(p->addressbook[k].sin_addr));
				close(sockfd);
				FD_CLR(sockfd, &(p->allset));
           		p->client[i] = -1;
            }
			
            
			for(k = 0; k <= p->maxi; k++)	/* echo to all clients */
			{
				if(i != k)
				{
					write(p->client[k], msg, BUFLEN);      
				}
			}
			
			if (--(p->nready) <= 0)
        		break;        /* no more readable descriptors */
		}
	}
	return (void*)dummy;
}


