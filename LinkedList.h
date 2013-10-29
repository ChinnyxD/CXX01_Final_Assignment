#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct ListNode
{
	unsigned char * memPtr;
	int sizeOfNodeInBytes;
	struct ListNode * nextListPtr;
};



typedef struct ListNode node;

//Linked lists
node * pfreeList;
node * pUsedList;
//typedef ListNode *ListNodePtr;
int * startMemPtr;
int * endMemPtr;



void initLinkedList(unsigned char * memory);
unsigned char * allocateMemory(int requestedBytes);
void printLinkedLists();