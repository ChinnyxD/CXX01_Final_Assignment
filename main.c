#include <stdio.h>
#include <stddef.h>
#include "LinkedList.h"

//static //16384

int main()
{
	unsigned char memory[1024*16]; 
	//Initialize linked lists
	ListNodePtr freeListPtr = NULL;
	ListNodePtr UsedListPtr = NULL;
	printf("Start mem add: %d, End mem add:%d \n", &memory[0], &memory[16383]);
	initLinkedList(&freeListPtr,&memory);
	//void * RAM = malloc(16384);
	
	printf("hello world\n");
	system("pause");
	return 0;
}
