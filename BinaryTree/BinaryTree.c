#include <stdio.h>
#include <malloc.h>
#include "BinaryTree.h"
//二叉树

BinaryTree *InitBinaryTree(){
	BinaryTree *T = (BinaryTree *)malloc(sizeof(BinaryTree));
	BiTNode *n = (BiTNode *)malloc(sizeof(BiTNode));
	n->elem = (BiTNodeElemType *)malloc(sizeof(BiTNodeElemType));
	T->This = n;
	return T;
}

void DestroyBinaryTree(BinaryTree *T){
	if(T){
		if(T->This){
			if(T->This->elem){
				free(T->This->elem);
			}
			free(T->This);
		}
		free(T);
		L = NULL;
	}
}


