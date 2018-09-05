#include <stdio.h>
#include <malloc.h>
#include "MyString.h"

MyString *myStringAssign(char *str){
	int i,str_length = 0;
	MyString *S = (MyString *)malloc(sizeof(MyString));
	if(!S) return NULL;
	while(*(str+str_length) != '\0'){
		str_length++;
	}
	str_length++;
	S->str = (char *)malloc(str_length*sizeof(char));
	if(!S->str){
		free(S);
		return NULL;
	}
	S->length = str_length - 1; 
	for(i=0;i<str_length;i++){
		*(S->str + i) = *(str + i);
	}
	return S;
}

int myStringLength(MyString *S){
	return S->length;
}

int isMyStringEmpty(MyString *S){
	if(S->length){
		return 0;
	}else{
		return 1;
	}
}

int clearMyString(MyString *S){
	if(S->str){
		free(S->str);
		S->str = NULL;
	}
	S->length = 0;
}

void destroyMyString(MyString *S){
	free(S->str);
	S->str = NULL;
	free(S);
	S = NULL;
}

int compareMyString(MyString *S1,MyString *S2){
	int i;
	int result = 0;
	for(i=0;i<S1->length && i<S2->length;i++){
		if(*(S1->str+i) != *(S2->str+i)){
			result = *(S1->str+i) - *(S2->str+i);
			break;
		}
	}
	if(result == 0){
		result = S1->length - S2->length;
	}
	return result;
}

MyString *copyMyString(MyString *S){
	int i;
	if(!S->str) return NULL;
	MyString *temp = (MyString *)malloc(sizeof(MyString));
	if(!temp) return NULL;
	temp->str = (char *)malloc((S->length+1)*sizeof(char));
	if(!temp->str){
		free(temp);
		return NULL;
	}
	temp->length = S->length; 
	for(i=0;i<S->length+1;i++){
		*(temp->str + i) = *(S->str + i);
	}
	return temp;
}

MyString *concatMyString(MyString *S1,MyString *S2){
	int i;
	if(!S1->str || !S2->str) return NULL;
	MyString *temp = (MyString *)malloc(sizeof(MyString));
	if(!temp) return NULL;
	temp->str = (char *)malloc((S1->length + S2->length + 1)*sizeof(char));
	if(!temp->str){
		free(temp);
		return NULL;
	}
	for(i=0;i<S1->length;i++){
		*(temp->str + i) = *(S1->str + i);
	}
	for(i=0;i<S2->length+1;i++){
		*(temp->str + S1->length + i) = *(S2->str + i);
	}
	temp->length = S1->length + S2->length;
	return temp;
}

int myStringIndexChar(MyString *S,char indexElem,int pos){
	int index = -1;
	int i;
	if(!S) return -1;
	for(i=pos;i<S->length;i++){
		if(*(S->str + i) == indexElem){
			index = i;
			break;
		}
	}
	return index;
}

int insertMyString(MyString *S1,MyString *S2,int pos){
	int i;
	if(!S2->str) return -1;
	if(pos < 0 || pos >= S1->length) return -1;
	S1->str = (char *)realloc(S1->str,(S1->length + S2->length + 1)*sizeof(char));
	if(!S1->str) return -1;
	for(i=S1->length;i>=pos;i--){
		*(S1->str + S2->length + i) = *(S1->str + i);
	}
	for(i=0;i<S2->length;i++){
		*(S1->str + pos + i) = *(S2->str + i);
	}
	S1->length += S2->length;
	return 0;
}

MyString *substrMyString(MyString *S,int start,int end){
	int i,length;
	if(start < 0 || start >= S->length || end <= 0 || end > S->length || end <= start) return NULL;
	MyString *temp = (MyString *)malloc(sizeof(MyString));
	if(!temp) return NULL;
	length = end - start;
	temp->str = (char *)malloc((length+1)*sizeof(char));
	if(!temp->str){
		free(temp);
		return NULL;
	}
	for(i=0;i<length;i++){
		*(temp->str + i) = *(S->str + start + i);
	}
	*(temp->str + length) = '\0';
	temp->length = length;
	return temp;
}
