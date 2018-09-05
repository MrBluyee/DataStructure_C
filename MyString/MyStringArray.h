/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MYSTRINGARRAY_H
#define _MYSTRINGARRAY_H
/* Includes ------------------------------------------------------------------*/
#include "MyString.h"
/* Exported types ------------------------------------------------------------*/

typedef struct MyStringArray_P
{
	MyString *mystring;
	struct MyStringArray_P *next;
}MyStringArray_P;

typedef struct MyStringArray{
	MyStringArray_P *This;
	MyStringArray_P *front;
	MyStringArray_P *tear;
	void (*clear)(struct MyStringArray *This);
	int (*isEmpty)(struct MyStringArray *This);
	int (*length)(struct MyStringArray *This);
	int (*index)(struct MyStringArray *This, MyString *e);
	int (*get)(struct MyStringArray *This, int index, MyString **e);
	int (*getFront)(struct MyStringArray *This, MyString **e);
	int (*getTear)(struct MyStringArray *This, MyString **e);
	int (*modify)(struct MyStringArray *This, int index, MyString *e);
	int (*insert)(struct MyStringArray *This, int index, MyString *e);
	int (*delete)(struct MyStringArray *This, int index, MyString **e);
	int (*tearPush)(struct MyStringArray *This, MyString *e);
	int (*tearPop)(struct MyStringArray *This, MyString **e);
	int (*frontPush)(struct MyStringArray *This, MyString *e);
	int (*frontPop)(struct MyStringArray *This, MyString **e);
	int (*traverse)(struct MyStringArray *This,int (*visit)(MyString **e));
}MyStringArray;

/* Exported macro ------------------------------------------------------------*/
MyStringArray *InitMyStringArray();
void DestroyMyStringArray(MyStringArray *strArray);

#endif