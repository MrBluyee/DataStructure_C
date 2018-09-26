/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ELEMTYPEDEFINE_H
#define _ELEMTYPEDEFINE_H

typedef int DLLSElemType;

typedef struct DLLSNode{
	DLLSElemType *elem;
	struct DLLSNode *prior;
	struct DLLSNode *next;
}DLLSNode;

#endif
