#include <stdio.h>
#include <malloc.h>
#include "BigInt.h"

unsigned long long StrLen(char *num){
	unsigned long long i = 0;
	while(*(num + i) != '\0'){
		i++;
	}
	return i;
}

int Pow10(int x){
	int result = 1;
	for (int i = 1; i < x; ++i)
	{
		result *= 10;
	}
	return result;
}

BigInt *BigIntInit(char *num, unsigned long long str_len){
	
	BigInt *big_int = NULL;
	unsigned long long num_dec_len; //大数的十进制位数
	unsigned long long num_dec_index = 0; //十进制数的游标
	unsigned char big_elem_remain; 
	unsigned long long big_elem_len;
	unsigned long long big_elem_index = 0; //big elem的游标

	if((!num) || (str_len == 0)) return NULL;
	if(str_len > StrLen(num)){
		printf("str lenth not match!\n");
		return NULL;
	} 
	big_int = (BigInt *)malloc(sizeof(BigInt));
 	if(!big_int) return NULL; 

	if(*num == '-'){
		num_dec_len = str_len - 1;
		big_int->sign = -1;
		num_dec_index = 1;
	}else if(*num == '+'){
		num_dec_len = str_len - 1;
		big_int->sign = 1;
		num_dec_index = 1;
	}else if((*num >= '0') && (*num <= '9')){
		num_dec_len = str_len;
		big_int->sign = 1;
		num_dec_index = 0;
	}else{
		printf("error format!\n");
		free(big_int);
		return NULL;
	}

	//限定每个int elem 最多存放9位十进制长度的数值
	big_elem_remain = num_dec_len % 9;
	big_elem_len = num_dec_len / 9;
	big_int->elem_num = big_elem_len;
	if(big_elem_remain != 0){
		big_int->elem_num++;
		big_elem_index = 1;
	}
	big_int->elem = (unsigned int *)malloc(big_elem_len*sizeof(unsigned int));
	if(!big_int->elem){
		free(big_int);
		return NULL;
	}
	*(big_int->elem) = 0;
	for (int i = 0; i < big_elem_remain; i++){
		if((*(num + i) >= '0') && (*(num + i) <= '9')){
			(*(big_int->elem)) += ((*(num + i) - '0') * Pow10(big_elem_remain - i));
		}else{
			free(big_int->elem);
			free(big_int);
			big_int = NULL;
			printf("error format!\n");
			break;
		}
	}
	if(!big_int) return NULL;
	num_dec_index += big_elem_remain;
	for (; big_elem_index < big_int->elem_num; big_elem_index++)
	{
		for(int j = 0; j < 9; j++){
			if((*(num + num_dec_index) >= '0') && (*(num + num_dec_index) <= '9')){
				*(big_int->elem + big_elem_index) += ((*(num + num_dec_index) - '0') * Pow10(9 - j));
			}else{
				free(big_int->elem);
				free(big_int);
				big_int = NULL;
				printf("error format!\n");
				break;
			}
			num_dec_index++;
		}
	}
	return big_int;
}

void BigIntPrint(BigInt *big_int){
	if(!big_int) return;
	if(!big_int->elem) return;
	if(big_int->sign == -1) printf("-");
	printf("%d",*(big_int->elem));
	for(int i = 1; i < big_int->elem_num; i++){
		printf("%09d",*(big_int->elem + i));
	}
	printf("\n");
}

void BigIntDestroy(BigInt *big_int){
	if(big_int->elem){
		free(big_int->elem);
	}
	if(big_int){
		free(big_int);
	}
	big_int = NULL;
}

BigInt *BigIntUnsignAdd(BigInt *big_a, BigInt *big_b){
	BigInt *result;
	unsigned long long elem_add_len;
	if((!big_a) || (!big_b)) return NULL;
	if((!big_a->elem) || (!big_b->elem)) return NULL;
	result = (BigInt *)malloc(sizeof(BigInt));
	if(!result) return NULL;
	if(big_a->elem_num > big_b->elem_num){
		elem_add_len = big_b->elem_num;
		result->elem_num = big_a->elem_num;
	}else if(big_a->elem_num == big_b->elem_num){
		elem_add_len = big_a->elem_num;
		result->elem_num = big_a->elem_num;
	}
		
	}
	for (unsigned long long i = 0; i < elem_add_len; ++i){
		*()
	}
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





