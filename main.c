
#include <stddef.h>
#include "memory.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/*! \mainpage This is the documentation for the application created for the final assignment for CXX01
 *
 * //\section intro_sec Introduction
 *	The main will initialize memory and then wait for user commands.
 */
int main()
{
	initMem();

	char cInput[10];
					
	while(strcmp("exit",cInput))
	{
		if(strcmp("alloc",cInput) == 0)
		{
			printf("> How many Bytes do you want to allocate: ");
			gets(cInput);
			
			printf("Returned pointer: %p\n",allocMem(atoi(cInput)));
		}
		else if(strcmp("free",cInput) == 0)
		{
			freeMemory(NULL);
		}
		else if(strcmp("print",cInput) == 0)
		{
			printMemory();
		}
		else if(strcmp("save",cInput) == 0)
		{
			saveToFileDB();
		}
		else if(strcmp("sort",cInput) == 0)
		{
			printf("> Choose sort method(1: By Address, 2: By size):");
			gets(cInput);
			
			if(atoi(cInput) > 0 && atoi(cInput) < 3)
			{
				sortAllLinkedList(atoi(cInput));
			}
			else
			{
				printf("Not a valid option!\n");
			}
		}
		printf("> Type alloc, free, print, save, load or exit: ");
		gets(cInput);
	}
	return 0;
}