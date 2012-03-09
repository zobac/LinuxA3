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
--		DATE:	    February 11, 2012		
--
--		DESIGNER:	Mike Zobac	
--
--		PROGRAMMER: Mike Zobac		
--
--		INTERFACE:  int main(void)		
--
--		RETURNS:	
--
--		NOTES:			
----------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    PGLOBALS    globals = (PGLOBALS) malloc(sizeof(GLOBALS));
    
    switch(argc)
    {
        case 1:
        {
            
            break;
        }
        
        case 2:
        {
            break;
        }
        
        case 3:
        {
            break;
        }    
    }
}
