
#include <stddef.h>
#include "memory.h"
#include <stdio.h>
#include <string.h>

int main()
{
	initMem();

	
	char input[10];
	
	allocMem(1);
	allocMem(2);
	allocMem(4);
	allocMem(8);
	allocMem(16);
	allocMem(32);
	allocMem(64);
	allocMem(128);
	allocMem(256);
	allocMem(512);
	allocMem(1024);
	allocMem(2048);
	allocMem(4096);

					
	while(strcmp("exit",input))
	{
		if(strcmp("alloc",input) == 0)
		{
			printf("How many Bytes do you want to allocate: ");
			gets(input);
			
			allocMem(atoi(input));
		}
		else if(strcmp("free",input) == 0)
		{
			freeMemory();
		}
		else if(strcmp("print",input) == 0)
		{
			printMemory();
		}
		else if(strcmp("save",input) == 0)
		{
			saveToFileDB();
		}
		else if(strcmp("load",input) == 0)
		{
		
		}
		printf("Type alloc,free,print or exit: ");
		gets(input);
	}
}