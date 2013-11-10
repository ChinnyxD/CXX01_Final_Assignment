#include "memory.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "ReadWriteFile.h";

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
		if(smallestBlock > pFreeNode->sizeOfNodeInBytes && pFreeNode->sizeOfNodeInBytes >= bytes && bytes < 16384)
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
		printf("Type the index number of the block you want to delete: ");
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
			pPrevUsedNode = (unsigned char*)pUsedNode;
			pUsedNode = (unsigned char*)pUsedNode->nextListPtr;
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
		pUsedNode->nextListPtr=NULL;
		pFreeNode->nextListPtr=pUsedNode;
		
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
		
		
		/*node *pFreeNode = (node*)pFreeList;
		node *pPrevFreeNode;
		node *pCheckForNode = (node*)((unsigned char*)pUsedNode+sizeof(node)+pUsedNode->sizeOfNodeInBytes);
		while(pFreeNode)
		{
			if(pFreeNode->nextListPtr)
			{
				node *pCheckForNode
			}
			
			/*
			if(pFreeNode == pCheckForNode) //Create new node with merge of next free node
			{
				printf("Found to merge with next block, Creating new node\n");
				pPrevFreeNode->nextListPtr = pUsedNode;
				pUsedNode->sizeOfNodeInBytes = pUsedNode->sizeOfNodeInBytes+sizeof(node)+pFreeNode->sizeOfNodeInBytes;
				pUsedNode->nextListPtr = pFreeNode->nextListPtr;
			}

			pPrevFreeNode = pFreeNode;
			pFreeNode = pFreeNode->nextListPtr;
		}
		
		
		
		/*node *pCheckForNode = (node*)((unsigned char*)pUsedNode+sizeof(node)+pUsedNode->sizeOfNodeInBytes);
		node *pFreeNode = (node*)pFreeList;
		
		int head = NULL;
		while(pFreeNode)
		{
			if(pFreeNode == pCheckForNode)
			{
				printf("Found 2 Free Blocks to merge!");
				pUsedNode->sizeOfNodeInBytes = pUsedNode->sizeOfNodeInBytes+sizeof(node)+pFreeNode->sizeOfNodeInBytes;
				if(pFreeNode == (node*)pFreeList)// if the node is the same as the head
				{
					pUsedNode->nextListPtr = pCheckForNode->nextListPtr;
					pFreeList = (unsigned char*) pUsedNode;
				}
				else
				{
					//go to the end of the linked list
					node *pPrevUsedList;
					while(pFreeNode->nextListPtr)
					{
						pFreeNode->nextListPtr;
					}
					//Append this node as a free Node
					pUsedNode->nextListPtr = NULL;
					pFreeNode->nextListPtr = pUsedNode;
				}
				
				pCheckForNode=NULL;
				printf("...Merged!\n");
			}
			pFreeNode = pFreeNode->nextListPtr;
		}
		
		/*else 
		{
			//Search for a another free block to merge
			while(pFreeNode)
			{
				if(pFreeNode == pCheckForNode)
				{
					printf("Found 2 Free Blocks to merge!");
				}
				pFreeNode = pFreeNode->nextListPtr;
			}
			if(pFreeList) // if there already are free blocks nodes in linked list
			{
				node *pFreeNode = (node*)pFreeList;
				while(pFreeNode->nextListPtr)
			}
			else //if there are no nodes in free linked list
			{
				pFreeList = (unsigned char*)pUsedNode
			}
			
			
			/*node *pPrevFreeNode;
			while(pFreeNode)
			{
				
				
				pPrevFreeNode = (node*)pFreeNode;
				pFreeNode = pFreeNode->nextListPtr;
			}*/
		//}
	}
}

void saveToFileDB()
{
	saveToFile(&memory);
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