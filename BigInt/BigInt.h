/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BIGINT_H
#define __BIGINT_H

typedef struct BigInt{
	unsigned int *elem;  //指向大数存放位置，序号0为低位  （4Bytes）范围(0 ～ 42 9496 7295),十进制长度10位
	unsigned long long elem_num;  //elem的个数  （8Bytes）范围(0 ～ 1844 6744 0737 0955 1615)
    char sign; //符号位，1表示正数，-1表示负数
}BigInt;



#endif