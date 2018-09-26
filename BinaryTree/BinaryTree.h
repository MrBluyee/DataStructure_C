/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BINARYTREE_H
#define __BINARYTREE_H
/* Includes ------------------------------------------------------------------*/
#include "ElemTypeDefine.h"
/* Exported types ------------------------------------------------------------*/

typedef struct BinaryTree{
	BiTNode *This;  
	void (*clear)(struct BinaryTree *This);
	int (*isEmpty)(struct BinaryTree *This);
}BinaryTree;

BinaryTree *InitBinaryTree();
void DestroyBinaryTree(BinaryTree *T);

#endif
