#include <stdio.h>

/**
 * Saves the allocated memory to a .db file. The user is able to define a filename. The allocated memory will not be deleted!
 * @param *pucMemory The pointer of memory
 */ 
void saveMemoryToFile(unsigned char *pucMemory);

/**
 * Saves the allocated memory to a .db file. The allocated memory will be deleted!
 * @param *pucMemory The pointer of memory 
 */
void saveToDB(unsigned char *pucMemory);