/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MYSTRING_H
#define _MYSTRING_H
/* Exported types ------------------------------------------------------------*/

typedef struct MyString{
	char *str;  
	int length;
}MyString;

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

/* Includes ------------------------------------------------------------------*/
#include "MyStringArray.h"


MyString *myStringAssign(char *str);
int myStringLength(MyString *S);
int isMyStringEmpty(MyString *S);
int clearMyString(MyString *S);
void destroyMyString(MyString *S);
int compareMyString(MyString *S1,MyString *S2);
MyString *copyMyString(MyString *S);
MyString *concatMyString(MyString *S1,MyString *S2);
int myStringIndexChar(MyString *S,char indexElem,int pos);
int insertMyString(MyString *S1,MyString *S2,int pos);
MyString *substrMyString(MyString *S,int start,int end);
MyStringArray *splitMyString(MyString *S,char splitElem);

#endif
