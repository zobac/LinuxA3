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
--	FUNCTION:	Client_setup	
--
--	DATE:	    March 12, 2012	
--
--	DESIGNER:	Chris Sim
--
--	PROGRAMMER: Chris Sim
--
--	INTERFACE:  void* client_setup(void* param)	
--
--	RETURNS:	void*
--
--	NOTES:		
---------------------------------------------------------------------------------------------------------------------------*/
void* client_setup(void* param)
{
	char* dummy = "";
	int i;
	PGLOBALS p = (PGLOBALS) param; 
	
	printf(" Remote Address:  %s\n", inet_ntoa(p->client_addr.sin_addr));

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
	
	return (void*)dummy;
}



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
	ssize_t n;
	int sockfd, i, k, bytes_to_read;
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
            fprintf(stderr, "n: %ld\n", n);
            fprintf(stderr, "data: %s\n", bp);
            /*
			while ((n = read(sockfd, bp, bytes_to_read)) > 0)
			{
				bp += n;
				bytes_to_read -= n;
			}
            */
			
			for(k = 0; k <= p->maxi; k++)	/* echo to all clients */
			{
				if(i != k)
				{
					sprintf(msg, "%s: %s", inet_ntoa(p->addressbook[k].sin_addr), buf);
					write(p->client[k], msg, BUFLEN);   
                    write(2, msg, BUFLEN);
				}
			}
			
			if (--(p->nready) <= 0)
        		break;        /* no more readable descriptors */
		}
	}
	return (void*)dummy;
}


