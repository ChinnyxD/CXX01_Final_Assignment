#include "ReadWriteFile.h"
#include <time.h>

void saveMemoryToFile(unsigned char *memory)
{
	//array to save pathname
	char pathName[100];
	printf("Specify a filename or path+filename: ");
	gets(pathName);
	
	//open file with the specified filename
	strcat(pathName,".db");
	fp = fopen(pathName, "w");
	
	//save characters
	printf("%d\n",memory);
	unsigned char *memoryPos = memory;
	int i;
	for(i=0;i<16384;i++)
	{
		fputc(*(unsigned char*)memoryPos,fp);
		memoryPos=(unsigned char*)memoryPos++;
	}
	//Close file,end
	fclose(fp);
}

void saveToDB(unsigned char* memory)
{
	char buffer [11] = "storage.db";
	fp = fopen(buffer, "w");
	
	//save characters
	printf("%d\n",memory);
	unsigned char *memoryPos = memory;
	int i;
	for(i=0;i<16384;i++)
	{
		fputc(*(unsigned char*)memoryPos,fp);
		memoryPos=(unsigned char*)memoryPos++;
	}
	//Close file,end
	fclose(fp);
}