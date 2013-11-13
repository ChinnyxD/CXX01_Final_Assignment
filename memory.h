/**
 * The Allocated memory acting as a RAM 
 */
unsigned char ucMemory[16384];

/**
 *The head of Free linked list 
 */
unsigned char *pucFreeList;

/**
 * The head of Used linked list 
 */
unsigned char *pucUsedList;

/**
 * Initializes the memory, linked lists and creates a free block
 */
void initMem();

/**
 * Allocates a block with a requested size in Bytes
 * @param iBytes Requested size in Bytes
 */
void * allocMem(int iBytes);

/**
 * Frees an allocated block.
 * 
 * The user can delete using command line commands or a pointer can be given to free.
 * @param pvMemToDelete Pointer of node that should be deleted
 */
void freeMemory(void* pvMemToDelete);

/**
 * Prints all Free nodes and used nodes
 */
void printMemory();

/**
 * Saves the memory to a file. The user is able to define a filename before saving. 
 */
void saveToFileDB();

/**
 * Sorts the linked list. The user is able to define to sort on addresses or on blocksize 
 * 
 * @param iSort input of sort method
 */
void sortAllLinkedList(int iSort);

/**
 * Check if Free blocks can be merged
 */ 
void checkForMerge();