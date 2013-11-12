#include "ReadWriteFile.h"
#include <time.h>
#include <string.h>

void saveMemoryToFile(unsigned char *pucMemory)
{
	//array to save pathname
	FILE *pFp;
	char cPathName[100];
	printf("Specify a filename or path+filename: ");
	gets(cPathName);
	
	//open file with the specified filename
	strcat(cPathName,".db");
	pFp = fopen(cPathName, "w");
	
	//save characters
	//printf("%d\n",memory);
	unsigned char *pucMemoryPos = pucMemory;
	int i;
	for(i=0;i<16384;i++)
	{
		fputc(*(unsigned char*)pucMemoryPos,pFp);
		pucMemoryPos=(unsigned char*)(pucMemoryPos)+1;
	}
	//Close file,end
	fclose(pFp);
}

void saveToDB(unsigned char* pucMemory)
{
	FILE *pFp;
	char cBuffer [11] = "storage.db";
	pFp = fopen(cBuffer, "w");
	
	//save characters
	//printf("%d\n",memory);
	unsigned char *pucMemoryPos = pucMemory;
	int i;
	for(i=0;i<16384;i++)
	{
		fputc(*(unsigned char*)pucMemoryPos,pFp);
		pucMemoryPos=(unsigned char*)(pucMemoryPos)+1;
	}
	//Close file,end
	fclose(pFp);
}