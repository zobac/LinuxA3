/*--------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    Wrappers.c  -	Wrapper functions for server
--
--	PROGRAM:	    TCP Chat Server
--
--	FUNCTIONS:		void SystemFatal(const char* message)
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
--	NOTES:          wrapper functions that are constantly used are placed in here
-----------------------------------------------------------------------------------------------------------------------*/

#include "wrappers.h"

/*------------------------------------------------------------------------------------------------------------------------
--	FUNCTION:	SystemFatal	
--
--	DATE:	    March 8, 2012	
--
--	DESIGNER:	Mike Zobac	
--
--	PROGRAMMER: Mike Zobac	
--
--	INTERFACE:  void SystemFatal(const char* message)	
--
--	RETURNS:	void
--
--	NOTES:		displays error messages with specific reason and exits
---------------------------------------------------------------------------------------------------------------------------*/
void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}


