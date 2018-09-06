#include <stdio.h>
#include <malloc.h>
#include "MyString.h"

int printMyString(MyString *str){
	printf("%s, ",str->str);
	printf("length :%d\n",str->length);
	return 0;
}

int printMyStringElem(MyString **str){
	printf("%s ",(*str)->str);
	return 0;
}

int main(void){
	int i;
	char words[] = {"without new experiences, something inside of us sleeps."};
	MyString *str_a = NULL;
	MyString *str_b = NULL;
	MyString *str_c = NULL;
	MyStringArray *str_array = NULL;

	str_a = myStringAssign("hello ");
	str_c = myStringAssign("hello ");

	printf("str_a :");
	printMyString(str_a);

	printf("is MyString empty: %d\n",isMyStringEmpty(str_a));

	if(compareMyString(str_a,str_c)==0){
		printf("str_a equals str_c\n");
	}else{
		printf("str_a is not equal str_c\n");
	}

	clearMyString(str_a);

	printf("is MyString empty: %d\n",isMyStringEmpty(str_a));

	if(compareMyString(str_a,str_c)==0){
		printf("str_a equals str_c\n");
	}else{
		printf("str_a is not equal str_c\n");
	}

	destroyMyString(str_a);
	str_a = copyMyString(str_c);
	

	str_b = myStringAssign("abaabcac");
	printf("str_b :");
	printMyString(str_b);

	destroyMyString(str_c);
	str_c = concatMyString(str_a,str_b);
	printf("str_c :");
	printMyString(str_c);
	
	printf("the MyString :");
	printMyString(str_b);
	//printf("index : %d\n",myStringIndexSubString(str_c,str_b,0));
	
	printf("the char \'B\' index: %d\n", myStringIndexChar(str_c,'B',0));

	insertMyString(str_a,str_b,str_a->length);
	printf("str_a :");
	printMyString(str_a);

	destroyMyString(str_c);
	str_c = substrMyString(str_a,0,5);
	printf("str_c :");
	printMyString(str_c);

	destroyMyString(str_c);
	str_c = myStringAssign(words);
	str_array = splitMyString(str_c,' ');
	str_array->traverse(str_array,printMyStringElem);

	destroyMyString(str_a);
	destroyMyString(str_b);
	destroyMyString(str_c);
	DestroyMyStringArray(str_array);
	return 0;
}