/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DLLQUEUE_H
#define _DLLQUEUE_H
/* Includes ------------------------------------------------------------------*/
#include "ElemTypeDefine.h"
/* Exported types ------------------------------------------------------------*/

typedef struct DLLQueue{
	DLLQNode *front;
	DLLQNode *tear;
	void (*clear)(struct DLLQueue *This);
	int (*isEmpty)(struct DLLQueue *This);
	int (*length)(struct DLLQueue *This);
	void (*riseTraverse)(struct DLLQueue *This,int (*visit)(DLLQElemType **e));
	void (*downTraverse)(struct DLLQueue *This,int (*visit)(DLLQElemType **e));
	int (*getHead)(struct DLLQueue *This, DLLQElemType **e);
	int (*enQueue)(struct DLLQueue *This, DLLQElemType *e);
	int (*deQueue)(struct DLLQueue *This, DLLQElemType **e);
}DLLQueue;

/* Exported macro ------------------------------------------------------------*/
DLLQueue *InitDLLQueue();
void DestroyDLLQueue(DLLQueue *Q);

#endif