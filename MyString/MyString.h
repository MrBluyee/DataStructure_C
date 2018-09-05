/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MYSTRING_H
#define _MYSTRING_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct MyString{
	char *str;  
	int length;
}MyString;

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

#endif
