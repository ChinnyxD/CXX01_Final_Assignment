
struct ListNode
{
	unsigned char * memPtr;
	int sizeOfNodeInBytes;
	struct ListNode *nextListPtr;
};

typedef struct ListNode ListNode;
typedef ListNode *ListNodePtr;
int * startMemPtr;
int * endMemPtr;

void initLinkedList(ListNodePtr *list, unsigned char * memory);
void allocateMemory(ListNodePtr *FreeList, ListNodePtr *UsedList,unsigned char * memory);