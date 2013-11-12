#include "memory.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "ReadWriteFile.h";

//this struct is 8 bytes 
struct ListNode
{
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
	printf("Array address: %d\n",&memory);
	printf("Block start:%d\n", pFreeList);
}

void * allocMem(int bytes)
{
	if(bytes < 1)
	{
		printf("Cannot allocate < 1!\n");
		return;
	}
	
	int smallestBlock = 16384;
	node *pPrevNode = NULL;
	node *pSmallestBlock = NULL;
	node *pPrevSmallestBlock = NULL;
	//placeholder to search for the smallest block
	node *pFreeNode = (node*) pFreeList;
	//Search for the smallest block as long there is a next node
	while(pFreeNode)
	{
		if(smallestBlock > pFreeNode->sizeOfNodeInBytes && pFreeNode->sizeOfNodeInBytes > bytes && bytes < 16376)
		{
			printf("Found smaller block @ %d\n",pFreeNode);
			smallestBlock = pFreeNode->sizeOfNodeInBytes;
			pPrevSmallestBlock = pPrevNode; 
			pSmallestBlock = pFreeNode;
		}
		if(pFreeNode->nextListPtr == NULL) // Check if there is nextPtr
		{
			break;
		}
		pPrevNode = pFreeNode;
		pFreeNode = pFreeNode->nextListPtr;
	}
	if(pSmallestBlock == NULL) //TODO write to file
	{
		printf("No block found! Try other size!\n");
		return;
	}
	
	//delete the pointer from the prev node

	//printf("memptr: %d\n",(pSmallestBlock));
	//printf("Size: %d\n",pSmallestBlock->sizeOfNodeInBytes);
	//printf("nextptr: %p\n",pSmallestBlock->nextListPtr);
	

	node *pNewUsedNode = (node*)((unsigned char*) pSmallestBlock);
	
	node *pNewFreeNode = (node*)((unsigned char*) (pSmallestBlock)+sizeof(node)+bytes);
	if(pFreeList == (unsigned char*)pSmallestBlock) //If the block is the beginning of the linked list
	{
		printf("New free node will be set in the beginning of the list!\n");

		pNewFreeNode->nextListPtr = NULL;
		pFreeList = (unsigned char*)pNewFreeNode;
	}
	else if(pSmallestBlock && pSmallestBlock->nextListPtr != NULL && pPrevNode) // if the block is the mid of the linked list
	{
		printf("New free node will be set with prev and next nodes!\n");
		pPrevSmallestBlock->nextListPtr=pNewFreeNode;
		pNewFreeNode->nextListPtr = pSmallestBlock->nextListPtr;
	}
	else //If the block is at the end of the list
	{
		printf("New free node will be set with prev node!\n");

		pPrevNode->nextListPtr = pNewFreeNode;
		printf("prev:%d, new next:%d\n",pPrevNode,pPrevNode->nextListPtr);
		pNewFreeNode->nextListPtr = NULL;
	}
	
	
	//Create new free block and store it in new node

	pNewFreeNode->sizeOfNodeInBytes=smallestBlock-bytes-sizeof(node)-sizeof(node);
	
	//Create new used block and store in linked list
	pNewUsedNode->sizeOfNodeInBytes=bytes;
	pNewUsedNode->nextListPtr = pUsedList;
	pUsedList = (unsigned char*) pNewUsedNode;

	return (unsigned char*)pNewUsedNode+8;
}

void freeMemory()
{
	node *pUsedNode = (node*) pUsedList;
	int index = 0;
	while(pUsedNode)
	{
		printf("index:%d, block:%d, block size:%d\n",index++,pUsedNode,pUsedNode->sizeOfNodeInBytes);
		pUsedNode = pUsedNode->nextListPtr;
	}
	if(index==0)
	{
		printf("No blocks available to free!\n");
		return;
	}
	else
	{
		int i;
		char input[10];	
		printf("> Type the index number of the block you want to delete: ");
		gets(input);
		int selectedNode = atoi(input);
		if(selectedNode >= index || selectedNode < 0)
		{
			printf("Not a valid index! returning to menu..\n");
			return;
		}
		node *pPrevUsedNode = NULL;
		//get selected node
		pUsedNode = (node*) pUsedList;
		for(i=0;i<selectedNode;i++)
		{
			pPrevUsedNode = (node*)(unsigned char*)pUsedNode;
			pUsedNode = (node*)(unsigned char*)pUsedNode->nextListPtr;
		}
		
		//deletion of node  //TODO
		if(pUsedList == (unsigned char*)pUsedNode) 	//If the node is at the beginning of the list
		{
			printf("Deleting head node!\n");
			if(pUsedNode->nextListPtr) // If this node has a next node, the head of the list will modified to the next node
			{
				pUsedList = (unsigned char*)pUsedNode->nextListPtr;
			}
			else
			{
				pUsedList = NULL;
			}
		}
		else if(pPrevUsedNode && pUsedNode && pUsedNode->nextListPtr)
		{
			printf("Deleting mid node!\n");
			pPrevUsedNode->nextListPtr = pUsedNode->nextListPtr;
		}
		else if(pPrevUsedNode && pUsedNode && pUsedNode->nextListPtr == NULL)
		{
			printf("Deleting end node\n");
			pPrevUsedNode->nextListPtr = NULL;
		}
		
		//add to free linked list
		node *pFreeNode = (node*)pFreeList;
		while(pFreeNode->nextListPtr)
		{
			pFreeNode=pFreeNode->nextListPtr;
		}
		//pUsedNode->nextListPtr=NULL;
		pFreeNode->nextListPtr=pUsedNode;
		pUsedNode->nextListPtr=NULL;
		
		//Check for merge
		pFreeNode = (node*)pFreeList;
		while(pFreeNode)
		{
			node *pCheckFreeNode = (node*)((unsigned char*)pFreeNode+sizeof(node)+pFreeNode->sizeOfNodeInBytes);
			node *pFreeCheckingNode = (node*)pFreeList;
			while(pFreeCheckingNode)
			{//TODO
				if(pCheckFreeNode == pFreeCheckingNode) //MERGE
				{
					printf("Found 2 Free blocks to merge!\n");
					pFreeNode->sizeOfNodeInBytes = pFreeNode->sizeOfNodeInBytes+sizeof(node)+pFreeCheckingNode->sizeOfNodeInBytes;
					pFreeNode->nextListPtr=pCheckFreeNode->nextListPtr;
					//pFreeCheckingNode=pFreeCheckingNode->nextListPtr;
					//pFreeCheckingNode=NULL;
					//break;
				}
				//if(pFreeCheckingNode!=NULL)
				pFreeCheckingNode=pFreeCheckingNode->nextListPtr;
			}
			pFreeNode=pFreeNode->nextListPtr;
		}
	}
}

void saveToFileDB()
{
	saveMemoryToFile((unsigned char*)&memory);
}
//bubblesort
void sortAllLinkedList(int sort)
{
	//Sort used nodes
	int changedFlag;
	do
	{
		changedFlag = 0;
		node *pPrevNode = NULL;
		node *pNode = (node*) pUsedList;
		node *pNodeNext = (node*)(unsigned char*) pNode->nextListPtr;
		while(pNode)
		{
			//apply algorithm if conditions are met for sorting
			if(pNode != NULL && pNodeNext != NULL && ((pNode->sizeOfNodeInBytes > pNodeNext->sizeOfNodeInBytes && sort == 2) || (sort == 1 && pNodeNext < pNode)))
			{
				//Check if the Head of the linked list needs to be updated
				if(pPrevNode == NULL)
					pUsedList = (unsigned char*)pNodeNext;
				else
					pPrevNode->nextListPtr=pNodeNext;
				pNode->nextListPtr=pNodeNext->nextListPtr;
				pNodeNext->nextListPtr=pNode;
				changedFlag = 1;
			}
			pPrevNode = pNode;
			pNode = pNode->nextListPtr;
			if(pNode != NULL)
			pNodeNext=pNode->nextListPtr;
		}		
	}
	while(changedFlag != 0);
	
	//sort free nodes
	do
	{
		changedFlag = 0;
		node *pPrevNode = NULL;
		node *pNode = (node*) pFreeList;
		node *pNodeNext = (node*)(unsigned char*) pNode->nextListPtr;
		while(pNode)
		{
			//apply algorithm if conditions are met for sorting
			if(pNode != NULL && pNodeNext != NULL && ((pNode->sizeOfNodeInBytes > pNodeNext->sizeOfNodeInBytes && sort == 2) || (sort == 1 && pNodeNext < pNode)))
			{
				//Check if the Head of the linked list needs to be updated
				if(pPrevNode == NULL)
					pFreeList = (unsigned char*)pNodeNext;
				else
					pPrevNode->nextListPtr=pNodeNext;
				pNode->nextListPtr=pNodeNext->nextListPtr;
				pNodeNext->nextListPtr=pNode;
				changedFlag = 1;
			}
			pPrevNode = pNode;
			pNode = pNode->nextListPtr;
			if(pNode != NULL)
			pNodeNext=pNode->nextListPtr;
		}		
	}
	while(changedFlag != 0);

}

void loadToMem()
{
	readFile((unsigned char*)&memory);
}

void printMemory()
{
	printf("==========Printing free blocks==========\n");
	node *pFreeNode = (node*) pFreeList;
	while(pFreeNode)
	{
		printf("----------Free Block----------\n");
		printf("Linked list address: %d\n",pFreeNode);
		printf("data storage address: %d\n",(unsigned char*)pFreeNode+sizeof(node));
		printf("size:%d\n",pFreeNode->sizeOfNodeInBytes);
		printf("nextPtr:%d\n",pFreeNode->nextListPtr);
		pFreeNode = pFreeNode->nextListPtr;
	}
		printf("==========Printing used blocks==========\n");
	node *pUsedNode = (node*) pUsedList;
	while(pUsedNode)
	{
		printf("----------Used Block----------\n");
		printf("Linked list address: %d\n",pUsedNode);
		printf("data storage address:%d\n",(unsigned char*)pUsedNode+sizeof(node));
		printf("size:%d\n",pUsedNode->sizeOfNodeInBytes);
		printf("nextPtr:%d\n",pUsedNode->nextListPtr);
		pUsedNode = pUsedNode->nextListPtr;
	}
	printf("==========END PRINT==========\n");
	
}