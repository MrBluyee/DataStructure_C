/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BIGINT_H
#define __BIGINT_H

typedef struct BigInt{
	unsigned long long elem_num;  //elem的个数  （8Bytes）范围(0 ～ 1844 6744 0737 0955 1615)
	unsigned int *elem;  //指向大数存放位置，序号0为低位  （4Bytes）范围(0 ～ 42 9496 7295),十进制长度10位，每个元素保存9位长度数据。
	struct BigInt *higher;  //higher指向更高位，higher = NULL为大数的head
	struct BigInt *lower;   //lower指向更低位，lower = NULL为大数的tear
    char sign; //符号位，1表示正数，-1表示负数，只有head node此符号位有效。
}BigInt;



#endif