#include <stdio.h>
#include <malloc.h>
#include "BigInt.h"

unsigned int StrLen(char *num){
	unsigned int i = 0;
	while(*(num + i) != '\0'){
		i++;
	}
	return i;
}

BigInt *BigIntInit(char *num, unsigned int str_len){
	
	BigInt *big_int = NULL;
	unsigned int num_len; //大数的十进制位数
	unsigned int num_index = 0; //十进制数的游标

	if((!num) || (str_len == 0)) return NULL;
	if(str_len > StrLen(num)){
		printf("str lenth not match!\n");
		return NULL;
	} 
	big_int = (BigInt *)malloc(sizeof(BigInt));
 	if(!big_int) return NULL; 

	big_int->higher = NULL;
	big_int->lower = NULL;

	if(*num == '-'){
		num_len = str_len - 1;
		big_int->sign = -1;
		num_index = 1;
	}else if(*num == '+'){
		num_len = str_len - 1;
		big_int->sign = 1;
		num_index = 1;
	}else if((*num >= '0') && (*num <= '9')){
		num_len = str_len;
		big_int->sign = 1;
		num_index = 0;
	}else{
		printf("error format!\n");
		free(big_int);
		return NULL;
	}

	big_int->elem_num = num_len;
	big_int->elem = (char *)malloc(big_elem_len*sizeof(char));
	if(!big_int->elem){
		free(big_int);
		return NULL;
	}
	for (int i = 0; i < num_len; i++){
		if((*(num + i) >= '0') && (*(num + i) <= '9')){
			*(big_int->elem + i) = *(num + i) - '0';
		}else{
			free(big_int->elem);
			free(big_int);
			big_int = NULL;
			printf("error format!\n");
			break;
		}
	}
	return big_int;
}

BigInt *BigIntFindHead(BigInt *big_int_node){
	BigInt *big_node_index = big_int_node;
	while(big_node_index->higher){
		big_node_index = big_node_index->higher;
	}
	return big_node_index;
}

BigInt *BigIntFindTear(BigInt *big_int_node){
	BigInt *big_node_index = big_int_node;
	while(big_node_index->lower){
		big_node_index = big_node_index->lower;
	}
	return big_node_index;	
}

void BigIntPrintNode(BigInt *big_int_node){
	if(!big_int_node) return;
	if(!big_int_node->elem) return;
	for(int i = 0; i < big_int_node->elem_num; i++){
		printf("%d", *(big_int_node->elem + i));	
	}
}

void BigIntPrint(BigInt *big_int){
	BigInt *big_node_index = big_int;
	if(!big_int) return;
	if(!big_int->elem) return;
	if(big_int->sign == -1){
		printf("-");
	}
	while(big_node_index){
		BigIntPrintNode(big_node_index);
		big_node_index = big_node_index->lower;
	}
	printf("\n");
}

unsigned long long BigIntGetLen(BigInt *big_int){
	BigInt *big_node_index;
	unsigned long long big_int_len;
	if(!big_int) return 0;
	big_int_len = big_int->elem_num;
	while(big_node_index->lower){
		big_int_len += big_node_index->lower->elem_num;
		big_node_index = big_node_index->lower;
	}
	return big_int_len;
}

//big_hi + big_lo -> big_hi
void BigIntCat(BigInt *big_hi, BigInt *big_lo){
	BigInt *big_hi_tear;
	if(!big_hi) return NULL;
	if(!big_hi->elem) return NULL;
	big_hi_tear = BigIntFindTear(big_hi);
	big_hi_tear->lower = big_lo;
}

int _BigIntCmpWithSameLen(BigInt *big_a, BigInt *big_b, unsigned long long big_len){
	unsigned long long big_a_acc = 0;
	unsigned long long big_b_acc = 0;
	int result = 0;
	BigInt *big_a_index = big_a;
	BigInt *big_b_index = big_b;
	for (unsigned long long i = 0; i < big_len; ++i)
	{
		unsigned int j = i - big_a_acc;
		unsigned int k = i - big_b_acc;
		if(j >= big_a_index->elem_num){
			big_a_acc += big_a_index->elem_num;
			big_a_index = big_a_index->lower;
			j = 0;
		}
		if(k >= big_b_index->elem_num){
			big_b_acc += big_b_index->elem_num;
			big_b_index = big_b_index->lower;	
			k = 0;		
		}

		if(*(big_a_index->elem + j) > *(big_b_index->elem + k)){
			result = 1;
			break;
		}else if(*(big_a_index->elem + j) < *(big_b_index->elem + k)){
			result = -1;
			break;	
		}
	}
	return result;
}

int BigIntCmp(BigInt *big_a, BigInt *big_b){
	unsigned long long big_a_len;
	unsigned long long big_b_len;
	int result;
	big_a_len = BigIntGetLen(big_a);
	big_b_len = BigIntGetLen(big_b);
	if(big_a_len > big_b_len){
		return 1;
	}else if(big_a_len < big_b_len){
		return -1;
	}else{
		if(big_a_len == 0){
			return 0;
		}else{
			result = _BigIntCmpWithSameLen(big_a, big_b, big_a_len);
		}
	}
	return result; 
}

BigInt *BigIntSplit(BigInt *big_int, unsigned int split_index){

}


void BigIntDestroy(BigInt *big_int){
	BigInt *big_int_node;
	BigInt *big_int_index;
	if(!big_int) return;
	big_int_node = BigIntFindHead(big_int);
	while(big_int_node){
		if(big_int_node->elem){
			free(big_int_node->elem);
		}
		big_int_index = big_int_node->lower;
        free(big_int_node);
        big_int_node = big_int_index;
	}
}

int BigIntUnsignAddNode(BigInt *result, BigInt *big_a, BigInt *big_b, int carry){
	BigInt *result_index;
	unsigned int elem_index;
	unsigned int interval;
	int result_carry = carry;

	if((!big_a) || (!big_b)) return 0;
	if((!big_a->elem) || (!big_b->elem)) return 0;
	if(result){
		if(result->elem) free(result->elem);
		free(result);
	}

	result = (BigInt *)malloc(sizeof(BigInt));
	if(!result_index){
		return 0; 
	} 
	result->higher = NULL;
	result->lower = NULL;

	return result_carry;
}

BigInt *BigIntUnsignSub(BigInt *big_a, BigInt *big_b){
	BigInt *result;
}


int main(int argc, char *argv[]){
	char *big_int_char;
	BigInt *big_int;

	big_int_char = (char *)malloc(65535 * sizeof(char));
	if(!big_int_char) return 0;

	printf("please input a big num\n");
	scanf("%s", big_int_char);
	big_int = BigIntInit(big_int_char, StrLen(big_int_char));
	BigIntPrint(big_int);

	BigIntDestroy(big_int);
	free(big_int_char);

	return 0;
}





