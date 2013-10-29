#include "memory.h"
#include "LinkedList.h"
#include <stddef.h>


void initMemory(unsigned char *memory)
{
	//Initialize linked lists
	ListNodePtr freeListPtr = NULL;
	ListNodePtr UsedListPtr = NULL;
	printf("Start mem add: %d, End mem add:%d \n", &memory[0], &memory[16383]);
	initLinkedList(&freeListPtr,&memory);
	printf("Opened initmem!\n");
}

void * memory_alloc(int bytes)
{
	
	while()
	{
		
	}
}