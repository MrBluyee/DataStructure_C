/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GLIST_H
#define _GLIST_H

typedef enum GLNodeElemTag{
	ATOM,  //原子结点
	LIST   //表结点
}GLNodeElemTag;

typedef struct GLNode{
	GLNodeElemTag tag;   //tag用于区分原子结点和表结点
	union content{              //原子结点和表结点的联合
		GLNodeElemType *elem;  //原子结点的指针
		struct GLNode *hp; //表结点的表头指针
	}content;
	struct GLNode *prior; //指向前一个元素的结点 
	struct GLNode *next; //指向下一个元素的结点 
}GLNode;

typedef struct GList{
	GLNode *Root;
}GList;

#endif