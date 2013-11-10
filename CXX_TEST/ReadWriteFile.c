#include "ReadWriteFile.h"


void saveToFile(unsigned char *memory)
{
	char pathName[100];
	unsigned char *memoryPos;
	printf("Specify a filename or path+filename: ");
	gets(pathName);
	
	strcat(pathName,".db");
	fp = fopen(pathName, "w");
	memoryPos = memory;
	unsigned char byte = (unsigned char)((unsigned char*)memoryPos);
	int i = 0;
	for(i=0;i<16384;i++)
	{
		printf("Address: %d",memoryPos);
		fputc(byte,fp);

		memoryPos=(unsigned char*)memoryPos++;
		unsigned char byte = (unsigned char)memoryPos;
	}
	fclose(fp);
	
}