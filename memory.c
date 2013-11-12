#include "Memory.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "ReadWriteFile.h"
#include <omp.h>

//this struct is 8 iBytes 
struct SListNode
{
	int iSizeOfNodeIniBytes;
	struct SListNode * pSNextNode;
};

typedef struct SListNode SNode;

void initMem()
{
	printf("Initializing Memory! Size of SNode:%d\n",sizeof(SNode));
	pucFreeList = (unsigned char*)&ucMemory;
	pucUsedList = (unsigned char*)&ucMemory[sizeof(unsigned char*)];
	//There are no used blocks yet!
	pucUsedList = NULL;	

	SNode *pSFreeNode =(SNode*) &ucMemory[(2*sizeof(unsigned char*))];
	pSFreeNode->iSizeOfNodeIniBytes=((16384)-(((2*sizeof(unsigned char*))+sizeof(SNode))));//(16*1024)-sizeof(pSFreeNode);
	pSFreeNode->pSNextNode=NULL;
	pucFreeList = (unsigned char*)pSFreeNode;
	printf("Array address: %p\n",&ucMemory);
	printf("Block start:%p\n", pucFreeList);
}

void * allocMem(int iBytes)
{
	if(iBytes < 1)
	{
		printf("Cannot allocate < 1!\n");
		return NULL;
	}
	
	int iSmallestBlock = 16384;
	SNode *pSPrevNode = NULL;
	SNode *pSSmallestBlock = NULL;
	SNode *pSPrevSmallestBlock = NULL;
	//placeholder to search for the smallest block
	SNode *pSFreeNode = (SNode*) pucFreeList;
	//Search for the smallest block as long there is a next SNode
	while(pSFreeNode)
	{
		if(iSmallestBlock > pSFreeNode->iSizeOfNodeIniBytes && pSFreeNode->iSizeOfNodeIniBytes >= iBytes && iBytes < 16376)
		{
			printf("Found smaller block @ %p\n",pSFreeNode);
			iSmallestBlock = pSFreeNode->iSizeOfNodeIniBytes;
			pSPrevSmallestBlock = pSPrevNode; 
			pSSmallestBlock = pSFreeNode;
		}
		if(pSFreeNode->pSNextNode == NULL) // Check if there is nextPtr
		{
			break;
		}
		pSPrevNode = pSFreeNode;
		pSFreeNode = pSFreeNode->pSNextNode;
	}
	
	if(pSSmallestBlock == NULL && iBytes < 16376) // Saves the ucMemory to a file, cleans, and continue alloc if requested iBytes < 16376
	{
		printf("-- Saved old ucMemory to file, Memory is cleaned and allocated!\n");
		saveToDB((unsigned char*)&ucMemory);
		initMem();
		return allocMem(iBytes);
	}
	else if(pSSmallestBlock == NULL) //TODO write to file
	{
		printf("Requested block size is too big!\n");
		return NULL;
	}
	
	//delete the pointer from the prev SNode

	//printf("memptr: %d\n",(pSSmallestBlock));
	//printf("Size: %d\n",pSSmallestBlock->iSizeOfNodeIniBytes);
	//printf("nextptr: %p\n",pSSmallestBlock->pSNextNode);
	

	SNode *pSNewUsedNode = (SNode*)((unsigned char*) pSSmallestBlock);
	if(pSSmallestBlock->iSizeOfNodeIniBytes > iBytes+sizeof(SNode)+1)
	{
		SNode *pSNewFreeNode = (SNode*)((unsigned char*) (pSSmallestBlock)+sizeof(SNode)+iBytes);
		if(pucFreeList == (unsigned char*)pSSmallestBlock) //If the block is the beginning of the linked list
		{
			//printf("New free SNode will be set in the beginning of the list!\n");

			pSNewFreeNode->pSNextNode = NULL;
			pucFreeList = (unsigned char*)pSNewFreeNode;
		}
		else if(pSSmallestBlock && pSSmallestBlock->pSNextNode != NULL && pSPrevNode) // if the block is the mid of the linked list
		{
			printf("New free SNode will be set with prev and next SNodes!\n");
			pSPrevSmallestBlock->pSNextNode=pSNewFreeNode;
			pSNewFreeNode->pSNextNode = pSSmallestBlock->pSNextNode;
		}
		else //If the block is at the end of the list
		{
			printf("New free SNode will be set with prev SNode!\n");

			pSPrevNode->pSNextNode = pSNewFreeNode;
			//printf("prev:%d, new next:%d\n",pSPrevNode,pSPrevNode->pSNextNode);
			pSNewFreeNode->pSNextNode = NULL;
		}
		//Create new free block and store it in new SNode
		pSNewFreeNode->iSizeOfNodeIniBytes=iSmallestBlock-iBytes-sizeof(SNode)-sizeof(SNode);
		pSNewUsedNode->iSizeOfNodeIniBytes=iBytes;
	}
	else // When it is not possible to split this block. This entire block will be referred to UsedBlock
	{
		printf("This block is not able to split, this block will take the full size of the free block!\n");
		if(pucFreeList == (unsigned char*)pSSmallestBlock) //If the block is the beginning of the linked list
		{
			if(pSSmallestBlock->pSNextNode) //next Node will be the head
			{
				pucFreeList = (unsigned char*)pSSmallestBlock;
			}
			else // When there is only 1 pSFreeNode in the list
			{
				pucFreeList = NULL;
			}
		}
		else if(pSPrevNode->pSNextNode && pSSmallestBlock->pSNextNode)
		{
			pSPrevNode->pSNextNode=pSSmallestBlock->pSNextNode;
		}
		else
		{
			pSPrevNode->pSNextNode=NULL;
		}
		pSNewUsedNode->iSizeOfNodeIniBytes=pSSmallestBlock->iSizeOfNodeIniBytes;
	}
	//Create new used block and store in linked list
	//pSNewUsedNode->iSizeOfNodeIniBytes=iBytes;
	pSNewUsedNode->pSNextNode = (SNode*)(unsigned char*)pucUsedList;
	pucUsedList = (unsigned char*) pSNewUsedNode;

	return (unsigned char*)pSNewUsedNode+sizeof(SNode);
}

void freeMemory(unsigned char* pucMemToDelete)
{
	SNode *pSUsedNode = (SNode*) pucUsedList;
	SNode *pSPrevUsedNode = NULL;
	int iIndex = 0;
	int iSelectedNode = 0;
	
	while(pSUsedNode)
	{
		printf("iIndex:%d, block:%p, block size:%d\n",iIndex++,pSUsedNode,pSUsedNode->iSizeOfNodeIniBytes);
		pSUsedNode = pSUsedNode->pSNextNode;
	}
	if(iIndex==0)
	{
		printf("No blocks available to free!\n");
		return;
	}
	else if(pucMemToDelete) // When an address is givenm to free
	{
		while(pucMemToDelete != (unsigned char*)pSUsedNode)
		{
			pSPrevUsedNode = (SNode*)(unsigned char*)pSUsedNode;
			pSUsedNode = (SNode*)(unsigned char*)pSUsedNode->pSNextNode;
		}
		if(pucMemToDelete != (unsigned char*)pSUsedNode)
		{
			printf("-- Did not find SNode at given address! Returning to menu!\n");
			return;
		}
	}
	else
	{
		
		char cInput[10];	
		printf("> Type the iIndex number of the block you want to delete: ");
		gets(cInput);
		iSelectedNode = atoi(cInput);
		if(iSelectedNode >= iIndex || iSelectedNode < 0)
		{
			printf("Not a valid iIndex! returning to menu..\n");
			return;
		}
		//get selected SNode
		pSUsedNode = (SNode*) pucUsedList;
		int i;
		for(i=0;i<iSelectedNode;i++)
		{
			pSPrevUsedNode = (SNode*)(unsigned char*)pSUsedNode;
			pSUsedNode = (SNode*)(unsigned char*)pSUsedNode->pSNextNode;
		}
	}
	


	
	//deletion of SNode  //TODO
	if(pucUsedList == (unsigned char*)pSUsedNode) 	//If the SNode is at the beginning of the list
	{
		printf("Deleting head SNode!\n");
		if(pSUsedNode->pSNextNode) // If this SNode has a next SNode, the head of the list will modified to the next SNode
		{
			pucUsedList = (unsigned char*)pSUsedNode->pSNextNode;
		}
		else
		{
			pucUsedList = NULL;
		}
	}
	else if(pSPrevUsedNode && pSUsedNode && pSUsedNode->pSNextNode)
	{
		printf("Deleting mid SNode!\n");
		pSPrevUsedNode->pSNextNode = pSUsedNode->pSNextNode;
	}
	else if(pSPrevUsedNode && pSUsedNode && pSUsedNode->pSNextNode == NULL)
	{
		printf("Deleting end SNode\n");
		pSPrevUsedNode->pSNextNode = NULL;
	}
	
	//add to free linked list
	SNode *pSFreeNode = (SNode*)pucFreeList;
	while(pSFreeNode)
	{
		if(pSFreeNode->pSNextNode)
			pSFreeNode=pSFreeNode->pSNextNode;
		else
			break;
	}
	//pSUsedNode->pSNextNode=NULL;
	if(!pucFreeList) // When pucFreeList has no blocks, Create new head
	{
		pucFreeList = (unsigned char*)pSUsedNode;
	}
	else
	{
		pSFreeNode->pSNextNode=pSUsedNode;
	}
	pSUsedNode->pSNextNode=NULL;
	
	checkForMerge();
}

void checkForMerge()
{
	sortAllLinkedList(1);
	int iChangedFlag;
	do
	{
		iChangedFlag = 0;
		SNode *pSPrevFreeNode=(SNode*)(unsigned char*)pucFreeList;
		SNode *pSFreeNode;
		if(pSPrevFreeNode->pSNextNode)
			pSFreeNode=(SNode*)(unsigned char*)pSPrevFreeNode->pSNextNode;
		while(pSFreeNode)
		{
			if((SNode*)pSPrevFreeNode->pSNextNode == (SNode*)pSFreeNode)
			{
				printf("Merged 2 Free blocks! @ address:%p\n",pSPrevFreeNode);
				pSPrevFreeNode->pSNextNode=pSFreeNode->pSNextNode;
				pSPrevFreeNode->iSizeOfNodeIniBytes += sizeof(SNode)+pSFreeNode->iSizeOfNodeIniBytes;
				if(pSFreeNode == (SNode*)(unsigned char*) pucFreeList)
				{
					pucFreeList = (unsigned char*)pSPrevFreeNode;
				}
				iChangedFlag = 1;
			}
			pSPrevFreeNode=pSFreeNode;
			if(pSFreeNode->pSNextNode)
			pSFreeNode=pSFreeNode->pSNextNode;
			else
			{
				pSFreeNode=NULL;
			}
		}
	}
	while(iChangedFlag != 0);
}

void saveToFileDB()
{
	saveMemoryToFile((unsigned char*)&ucMemory);
}

//bubblesort
void sortAllLinkedList(int iSort)
{
	//Sort used SNodes
	int iChangedFlag;
	//omp_set_num_threads(4);
	#pragma omp parallel
	{
		do
		{

			iChangedFlag = 0;
			SNode *pSPrevNode = NULL;
			SNode *pSNode = (SNode*) pucUsedList;
			if(!pSNode)
				{return;}
			SNode *pSNodeNext = NULL;
			if(pSNode->pSNextNode)
			pSNodeNext =(SNode*)(unsigned char*) pSNode->pSNextNode;
			while(pSNode)
			{
				//apply algorithm if conditions are met for sorting
				if(pSNode != NULL && pSNodeNext != NULL && ((pSNode->iSizeOfNodeIniBytes > pSNodeNext->iSizeOfNodeIniBytes && iSort == 2) || (iSort == 1 && pSNodeNext > pSNode)))
				{
					//Check if the Head of the linked list needs to be updated
					if(pSPrevNode == NULL)
						pucUsedList = (unsigned char*)pSNodeNext;
					else
						pSPrevNode->pSNextNode=pSNodeNext;
					pSNode->pSNextNode=pSNodeNext->pSNextNode;
					pSNodeNext->pSNextNode=pSNode;
					iChangedFlag = 1;
				}
				pSPrevNode = pSNode;
				pSNode = pSNode->pSNextNode;
				if(pSNode != NULL)
				pSNodeNext=pSNode->pSNextNode;
			}		
		}
		while(iChangedFlag != 0);
	}
	//sort free SNodes
	do
	{
		iChangedFlag = 0;
		SNode *pSPrevNode = NULL;
		SNode *pSNode = (SNode*) pucFreeList;
		SNode *pSNodeNext = (SNode*)(unsigned char*) pSNode->pSNextNode;
		while(pSNode)
		{
			//apply algorithm if conditions are met for sorting
			if(pSNode != NULL && pSNodeNext != NULL && ((pSNode->iSizeOfNodeIniBytes > pSNodeNext->iSizeOfNodeIniBytes && iSort == 2) || (iSort == 1 && pSNodeNext < pSNode)))
			{
				//Check if the Head of the linked list needs to be updated
				if(pSPrevNode == NULL)
					pucFreeList = (unsigned char*)pSNodeNext;
				else
					pSPrevNode->pSNextNode=pSNodeNext;
				pSNode->pSNextNode=pSNodeNext->pSNextNode;
				pSNodeNext->pSNextNode=pSNode;
				iChangedFlag = 1;
			}
			pSPrevNode = pSNode;
			pSNode = pSNode->pSNextNode;
			if(pSNode != NULL)
			pSNodeNext=pSNode->pSNextNode;
		}		
	}
	while(iChangedFlag != 0);
}



void printMemory()
{
	printf("==========Printing free blocks==========\n");
	SNode *pSFreeNode = (SNode*) pucFreeList;
	while(pSFreeNode)
	{
		printf("----------Free Block----------\n");
		printf("Linked list address: %p\n",pSFreeNode);
		printf("data storage address: %p\n",(unsigned char*)pSFreeNode+sizeof(SNode));
		printf("size:%d\n",pSFreeNode->iSizeOfNodeIniBytes);
		printf("nextPtr:%p\n",pSFreeNode->pSNextNode);
		pSFreeNode = pSFreeNode->pSNextNode;
	}
		printf("==========Printing used blocks==========\n");
	SNode *pSUsedNode = (SNode*) pucUsedList;
	while(pSUsedNode)
	{
		printf("----------Used Block----------\n");
		printf("Linked list address: %p\n",pSUsedNode);
		printf("data storage address:%p\n",(unsigned char*)pSUsedNode+sizeof(SNode));
		printf("size:%d\n",pSUsedNode->iSizeOfNodeIniBytes);
		printf("nextPtr:%p\n",pSUsedNode->pSNextNode);
		pSUsedNode = pSUsedNode->pSNextNode;
	}
	printf("==========END PRINT==========\n");
	
}