#include <stdio.h>
#include <stddef.h>
#include "memory.h"


static unsigned char ram[16*1024];

char *pMem_Start;
int *allocated_Mem;

int main()
{
	initMem();
	allocMem(0);


	
	
//	printf("block Size:%d\n",sizeof(pFreeList));
	//store node in array
	/*node* firstnode = (node*)&RAM[8];
	firstnode->memPtr=&ram[4];
	firstnode->sizeOfNodeInBytes=8;
	firstnode->nextListPtr=NULL;*/
	
	//testing reading node
	/*node testnode = *(node*)&RAM[0];
	printf("memptr: %d\n",testnode.memPtr);
	printf("Size: %d\n",testnode.sizeOfNodeInBytes);
	printf("nextptr: %d\n",testnode.nextListPtr);*/
	system("pause");
}