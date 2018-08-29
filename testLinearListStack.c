#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

int main(void)
{
	int i;
	char string[] = "abcdefgh";
	ElemType elem;
	LinearListStack *stack = InitLinearListStack();
	printf("stack is empty:%d\n",stack->isEmpty(stack));
	for (i = 0; i < 8; i++){
		stack->push(stack,string+i);
	}
	printf("stack is empty:%d\n");
	stack->risePrint(stack);
	printf("stack is empty:%d\n",stack->isEmpty(stack));
	printf("stack length:%d\n",stack->length(stack));
	stack->clear(stack);
	DestroyLinearListStack(stack);
	return 0;
}