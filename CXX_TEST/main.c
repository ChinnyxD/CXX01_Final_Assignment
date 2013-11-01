
#include <stddef.h>
#include "memory.h"
#include <stdio.h>
#include <string.h>

int main()
{
	initMem();


	
	
//	printf("block Size:%d\n",sizeof(pFreeList));
	//store node in array
	/*node* firstnode = (node*)&RAM[8];
	firstnode->memPtr=&ram[4];
	firstnode->sizeOfNodeInBytes=8;
	firstnode->nextListPtr=NULL;*/
	
	//testing reading node
	/*node testnode = *(node*)&RAM[0];
	printf("memptr: %d\n",testnode.memPtr);
	printf("Size: %d\n",testnode.sizeOfNodeInBytes);
	printf("nextptr: %d\n",testnode.nextListPtr);*/
	
	char input[10];
	while(strcmp("exit",input))
	{
		if(strcmp("alloc",input) == 0)
		{
			printf("Type how many Bytes you want to allocate: ");
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
		printf("Type alloc,free,print or exit: ");
		gets(input);
	}
}