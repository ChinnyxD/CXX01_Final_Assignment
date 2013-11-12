#include "ReadWriteFile.h"


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
		/*printf("%c",*(unsigned char*)memoryPos);
		if(i==10)
		{system("pause");}*/
		fputc(*(unsigned char*)memoryPos,fp);

		memoryPos=(unsigned char*)memoryPos++;
	}
	//Close file,end
	fclose(fp);
}

void readFile(unsigned char *memory)
{
	printf("%d\n",memory);
}