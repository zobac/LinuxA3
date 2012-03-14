/*--------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:    Wrappers.c  -
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
--	NOTES:		
---------------------------------------------------------------------------------------------------------------------------*/
void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}


