#define MAX_ADDR_LENGTH 1000

struct listNode
{ 
char addr[MAX_ADDR_LENGTH]; 

struct listNode *next; 
};

struct listNode thisNode; 

struct listNode *pListStart = NULL; 

char *aString = “Midterm Exam 2 of CS23200”; 
