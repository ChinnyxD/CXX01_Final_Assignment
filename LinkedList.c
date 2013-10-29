#include "LinkedList.h"
#include <stddef.h>

void initLinkedList(unsigned char *memory)
{
	startMemPtr = memory;
	endMemPtr = memory+16383;
	printf("Start mem add: %d End mem add:%d\n", startMemPtr, endMemPtr);
	node *freeNode;
	freeNode = (node *)malloc(sizeof(node));
	freeNode->memPtr = startMemPtr;
	freeNode->sizeOfNodeInBytes = (16*1024);
	freeNode->nextListPtr = NULL;
	pfreeList = freeNode;
	
	/*node *usedNode;
	usedNode = (node *)malloc(sizeof(node));
	usedNode->memPtr=0;
	usedNode->sizeOfNodeInBytes=0;
	usedNode->nextListPtr=NULL;
	pUsedList = usedNode;*/
	pUsedList = NULL;
	//Print all avail nodes
	node * curr = pfreeList;
	while(curr) 
	{
		printf("bytes avail: %d\n", curr->sizeOfNodeInBytes);
		curr = curr->nextListPtr ;
	}
	allocateMemory(8);
	allocateMemory(5);
	allocateMemory(6);
	printLinkedLists();
	printf("Opened inited Linked list\n");
}

unsigned char * allocateMemory(int requestedBytes)
{
	//Searches for a free block, the program will split this block
	node * pFreeNode = pfreeList;
	while(pFreeNode) 
	{
		if(pFreeNode->sizeOfNodeInBytes > requestedBytes)
		{
			node *UsedNode; // Just created node
			UsedNode = (node *)malloc(sizeof(node));
			UsedNode->memPtr = pFreeNode->memPtr;
			UsedNode->sizeOfNodeInBytes = requestedBytes;
			UsedNode->nextListPtr = NULL;
			if(!pUsedList)
			{
				//pUsedList = (node*)malloc(sizeof(node));
				pUsedList = UsedNode;
			}
			else
			{
				UsedNode->nextListPtr = pUsedList;
				pUsedList = UsedNode;
			}
			
			//modify Free Linked list
			pFreeNode->memPtr = pFreeNode->memPtr+requestedBytes;
			pFreeNode->sizeOfNodeInBytes = (pFreeNode->sizeOfNodeInBytes-requestedBytes);
			return UsedNode->memPtr;
		}
		pFreeNode = pFreeNode->nextListPtr ;
	}
	return NULL; // if no free space left, return NULL as ERROR
}

void printLinkedLists()
{
	printf("============Free blocks============\n");

	node * pFreeNode = pfreeList;
	while(pFreeNode) 
	{
		printf("Address:%d, Reserved B:%d\n",pFreeNode->memPtr,pFreeNode->sizeOfNodeInBytes);
		pFreeNode =  pFreeNode->nextListPtr;
	}
	printf("============Used blocks============\n");
	//pUsedList;
	node * pUsedList = pUsedList;
	while(pUsedList) 
	{
		printf("Address:%d, Reserved B:%d\n",pUsedList->memPtr,pUsedList->sizeOfNodeInBytes);
		pUsedList = pUsedList->nextListPtr;
	}
}

void freeMemory();

//void 
