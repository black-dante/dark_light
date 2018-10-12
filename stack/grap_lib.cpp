#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

void print_prog_bar(int proc);
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function print_prog_bar()
 *
 *	 draws progress bar
 *
 *   @param[in] proc how much to fill the progress bar
 *
 */	
void print_prog_bar(int proc)
	{
		assert(proc >= 0);
		assert(proc <= 100);
		
		printf("% 4d%% [", proc);
		for(int i = 0; i < proc/2; i++)
			printf("=");
		
		for(int i = proc/2; i < 50; i++)
			printf(".");
			printf("]");
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	
	
