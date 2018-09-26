/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ELEMTYPEDEFINE_H
#define _ELEMTYPEDEFINE_H

typedef int DLLQElemType;

typedef struct DLLQNode{
	DLLQElemType *elem;
	struct DLLQNode *prior;
	struct DLLQNode *next;
}DLLQNode;

#endif
