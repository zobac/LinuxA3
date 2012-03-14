/*--------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    Client.c - 
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

#include "client.h"
#include "includes.h"

/*------------------------------------------------------------------------------------------------------------------------
--	FUNCTION:		
--
--	DATE:	    March , 2012	
--
--	DESIGNER:	
--
--	PROGRAMMER: 	
--
--	INTERFACE:  	
--
--	RETURNS:	
--
--	NOTES:		
---------------------------------------------------------------------------------------------------------------------------*/
void * sendText( void *ptr )
{
	char 	sbuf[BUFLEN];
	int		*clSocket = (int *) ptr; 
	
	while(1)
	{
		/* Get user input */
		fgets (sbuf, BUFLEN, stdin);

		/* Send user input to  server */
		send (*clSocket, sbuf, BUFLEN, 0);
	}

	return(0);
}





