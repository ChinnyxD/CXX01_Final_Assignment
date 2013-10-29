#include "memory.h"


void initMemory(unsigned char *memory)
{
	//Initialize linked lists
	printf("Start mem add: %d End mem add:%d \n", &memory[0], &memory[16383]);
	initLinkedList(&memory);
	printf("Opened initmem!\n");
}

void * memory_alloc(int bytes)
{
	
	
	
}