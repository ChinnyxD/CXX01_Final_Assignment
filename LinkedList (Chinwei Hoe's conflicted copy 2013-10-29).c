#include "LinkedList.h"
#include <stddef.h>

void initLinkedList(ListNodePtr *freeListPtr, unsigned char *memory)
{
	startMemPtr = memory;
	endMemPtr = memory+16383;
	printf("Start mem add: %d End mem add: %d\n", startMemPtr, endMemPtr);
	ListNode freeNode;
	freeNode.memPtr = memory;
	freeNode.sizeOfNodeInBytes = (16*1024);
	freeNode.nextListPtr = NULL;
	freeListPtr = &freeNode;
	printf("Opened inited Linked list\n");
}

void allocateMemory(ListNodePtr *freeList, ListNodePtr *usedList, unsigned char *memory)
{
	//Searches for a free block, the program will split this block
	
	
}

void freeMemory();

//void 
