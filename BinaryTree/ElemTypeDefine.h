/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ELEMTYPEDEFINE_H
#define _ELEMTYPEDEFINE_H

//**********************************************************************//
typedef int BiTNodeElemType;

typedef struct BiTNode{
	BiTNodeElemType *elem;
	int id;
	struct BiTNode *parent;
	struct BiTNode *left;
	struct BiTNode *right;
}BiTNode;

//**********************************************************************//
typedef int DLLSElemType;

typedef struct DLLSNode{
	DLLSElemType *elem;
	struct DLLSNode *prior;
	struct DLLSNode *next;
}DLLSNode;

//**********************************************************************//
typedef int DLLQElemType;

typedef struct DLLQNode{
	DLLQElemType *elem;
	struct DLLQNode *prior;
	struct DLLQNode *next;
}DLLQNode;

#endif
