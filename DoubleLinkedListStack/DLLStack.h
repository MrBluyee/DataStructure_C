/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DLLSTACK_H
#define _DLLSTACK_H
/* Includes ------------------------------------------------------------------*/
#include "ElemTypeDefine.h"
/* Exported types ------------------------------------------------------------*/

typedef struct DLLStack{
	DLLSNode *front;
	DLLSNode *tear;
	void (*clear)(struct DLLStack *This);
	int (*isEmpty)(struct DLLStack *This);
	int (*length)(struct DLLStack *This);
	void (*riseTraverse)(struct DLLStack *This,int (*visit)(DLLSElemType **e));
	void (*downTraverse)(struct DLLStack *This,int (*visit)(DLLSElemType **e));
	int (*getTopElem)(struct DLLStack *This, DLLSElemType **e);
	int (*pushElem)(struct DLLStack *This, DLLSElemType *e);
	int (*popElem)(struct DLLStack *This, DLLSElemType **e);
}DLLStack;

/* Exported macro ------------------------------------------------------------*/
DLLStack *InitDLLStack();
void DestroyDLLStack(DLLStack *S);

#endif