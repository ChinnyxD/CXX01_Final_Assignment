#include "memory.h"
#include <stddef.h>
struct ListNode
{
	unsigned char * memPtr;
	int sizeOfNodeInBytes;
	struct ListNode * nextListPtr;
};

typedef struct ListNode node;

void initMem()
{
	printf("Initializing Memory!\n");
	unsigned char *pFreeList = (unsigned char*)&memory[0];
	unsigned char *pUsedList = (unsigned char*)&memory[4];
	
	node *freeNode = (node*) &memory[8];
	freeNode->memPtr=&memory[12];
	freeNode->sizeOfNodeInBytes=(16*1024);//(16*1024)-sizeof(freeNode);
	freeNode->nextListPtr=NULL;
	printf("Pointer to:%d\n",freeNode);
	pFreeList = freeNode;
	printf("Pointer to2:%d\n",pFreeList);
	pUsedList = NULL;
	//printf("%d",sizeof(freeNode));
}

void * allocMem(int bytes)
{
	unsigned char *pFreeList = (unsigned char*)&memory[0];
	printf("Pointer to3:%d\n",pFreeList);
	
	node testnode = *(node*)&pFreeList;
	printf("memptr: %d\n",testnode.memPtr);
	printf("Size: %d\n",testnode.sizeOfNodeInBytes);
	printf("nextptr: %d\n",testnode.nextListPtr);
	
	//while()
	return 0;
}