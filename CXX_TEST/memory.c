#include "memory.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct ListNode
{
	//unsigned char * memPtr;
	int sizeOfNodeInBytes;
	struct ListNode * nextListPtr;
};

typedef struct ListNode node;

void initMem()
{
	printf("Initializing Memory! Size of node:%d\n",sizeof(node));
	//printf("Block start:%d\n", &memory);
	pFreeList = (unsigned char*)&memory;
	pUsedList = (unsigned char*)&memory[sizeof(unsigned char*)];
	//There are no used blocks yet!
	pUsedList = NULL;	

	node *freeNode =(node*) &memory[(2*sizeof(unsigned char*))];
	freeNode->sizeOfNodeInBytes=((16384)-(((2*sizeof(unsigned char*))+sizeof(node))));//(16*1024)-sizeof(freeNode);
	freeNode->nextListPtr=NULL;
	pFreeList = (unsigned char*)freeNode;
	printf("Block start:%d\n", pFreeList);
}

void * allocMem(int bytes)
{
	int smallestBlock = 16384;
	node *pPrevNode = NULL;
	node *pSmallestBlock = NULL;
	//placeholder to search for the smallest block
	node *pFreeNode = (node*) pFreeList;
	//Search for the smallest block as long there is a next node
	while(pFreeNode)
	{
		if(smallestBlock > pFreeNode->sizeOfNodeInBytes && pFreeNode->sizeOfNodeInBytes >= bytes)
		{
			printf("Found smaller block @ %d\n",pFreeNode);
			smallestBlock = pFreeNode->sizeOfNodeInBytes;
			pSmallestBlock = pFreeNode;
		}
		pPrevNode = pFreeNode;
		pFreeNode = pFreeNode->nextListPtr;
	}
	
	printf("memptr: %d\n",(pSmallestBlock));
	printf("Size: %d\n",pSmallestBlock->sizeOfNodeInBytes);
	printf("nextptr: %p\n",pSmallestBlock->nextListPtr);
	
	//Create new free block and store it in new node
	//node *freeNode = ((node*) &memory)+(2*sizeof(unsigned char*));
	
	node *pNewUsedNode = (node*)((unsigned char*) pSmallestBlock);
	pNewUsedNode->sizeOfNodeInBytes=bytes;
	pNewUsedNode->nextListPtr = pUsedList;
	pUsedList = (unsigned char*) pNewUsedNode;
	
	node *pNewFreeNode = (node*)((unsigned char*) (pSmallestBlock)+sizeof(node)+bytes);
	pNewFreeNode->sizeOfNodeInBytes=smallestBlock-bytes-sizeof(node);
	if(pFreeList == (unsigned char*)pSmallestBlock) //If the block is the beginning of the linked list
	{
		printf("New free node will be set in the beginning of the list!\n");

		pNewFreeNode->nextListPtr = NULL;
		pFreeList = (unsigned char*)pNewFreeNode;
		

	}
	else if(pSmallestBlock && pSmallestBlock->nextListPtr && pPrevNode) // if the block is the mid of the linked list
	{
		printf("New free node will be set with prev and next nodes!\n");
		//the prev node will point to this node
		pPrevNode->nextListPtr=pNewFreeNode;
		pNewFreeNode->nextListPtr = pSmallestBlock->nextListPtr;
		//pFreeList = pNewFreeNode;
	}
	else //If the block is at the end of the list
	{
		printf("New free node will be set with prev node!\n");
		pNewFreeNode->nextListPtr = NULL;
	}
	return (unsigned char*)pNewUsedNode+8;
}

void printMemory()
{
	printf("==========Printing free blocks==========\n");
	node *pFreeNode = (node*) pFreeList;
	while(pFreeNode)
	{
		printf("----------Free Block----------\n");
		printf("Free block Linked list address: %d\n",pFreeNode);
		printf("Free block data storage address: %d\n",(unsigned char*)pFreeNode+sizeof(node));
		printf("Free block size:%d\n",pFreeNode->sizeOfNodeInBytes);
		printf("Free block nextPtr:%d\n",pFreeNode->nextListPtr);
		pFreeNode = pFreeNode->nextListPtr;
	}
		printf("==========Printing used blocks==========\n");
	node *pUsedNode = (node*) pUsedList;
	while(pUsedNode)
	{
		printf("----------Used Block----------\n");
		printf("Used block Linked list address: %d\n",pUsedNode);
		printf("Used block data storage address:%d\n",(unsigned char*)pUsedNode+sizeof(node));
		printf("Used block size:%d\n",pUsedNode->sizeOfNodeInBytes);
		printf("Used block nextPtr:%d\n",pUsedNode->nextListPtr);
		pUsedNode = pUsedNode->nextListPtr;
	}
	printf("==========END PRINT==========\n");
	
}