

unsigned char memory[16384];

unsigned char *pFreeList;
unsigned char *pUsedList;

void initMem();
void * allocMem(int bytes);
void printMemory();
