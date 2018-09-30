#include <malloc.h>
#include "Glist.h"

GList *initGList(MyString *gListStr){
	int i=0,start=0,end=0;
	GList *L = (GList *)malloc(sizeof(GList));
	GLNode *listp = NULL;
	GLNode *nodep = NULL;
	if(!L) return NULL;
	if(!gListStr) return L;
	if(bracketMatching(gListStr) == 0){
		printf("format error\n");
		return L;
	} return L;
	if(*(gListStr+i) != '('){
		printf("format error\n");
		return L;
	}
	while(*(gListStr+i) != '\0'){
		if(*(gListStr+i) == '('){
			if(i > 0){
				if(*(gListStr+i - 1) == '('){
					GLNode *n = (GLNode*)malloc(sizeof(GLNode));
					n->tag = LIST;
					listp = n->content.hp;
					n->prior = NULL;
					L->front = n;
					nodep = n;
					L->tear = n;	
				}else if(*(gListStr+i - 1) == ','){

				}
			}
			start = i + 1;
		}else if(*(gListStr+i) == ','){
			if(*(gListStr+i-1) != ')'){
				if(i > 0){
					end = i - 1;
				}
				if(start != end){
					GLNode *n = (GLNode*)malloc(sizeof(GLNode));
					n->tag = ATOM;
					MyString *subelem = substrMyString(gListStr,start,end);
					n->content.elem = subelem;
					n->prior = listp;
					listp->next = n;
					listp = n;
				}
			}else{

			}
		}else if(*(gListStr+i) == ')'){
			if(*(gListStr+i-1) != ')'){
				end = i - 1;
			}
		}
		i++;
	}

}

int createGList(GLNode *p,MyString *gListStr){
	int i;
	GLNode *temp = NULL;
	MyString *elemstr = NULL;
	MyString *leftstr = NULL;
	MyString *substr = substrMyString(gListStr,1,gListStr->length-1);//脱去括号
	if(!substr){
		p->next = NULL;
	}else{
		do{
			if(*(substr->str) != '('){
				i = myStringIndexChar(substr,',',0);
				if(i != -1){
					elemstr = substrMyString(substr,0,i);//提取表头
					leftstr = substrMyString(substr,i+1,substr->length);//提取剩余部分
					destroyMyString(substr);
					substr = leftstr;
				}else{
					elemstr = substrMyString(substr,0,substr->length);
					destroyMyString(substr);
				}
				temp = (GLNode*)malloc(sizeof(GLNode));
				if(temp){
					temp->tag = ATOM;
					temp->content.elem = elemstr;
					temp->prior = p;
					p->next = temp;
					p = temp;
				}else{
					p->next = NULL;
				}
			}else{
				
			}
		}while(i != -1);
	}
}







