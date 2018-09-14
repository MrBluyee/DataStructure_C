#include <stdio.h>
#include <malloc.h>
#include<math.h>
#include "MyStatisticsMath.h"

//求最小值
double getMin(double *array,int length){
	int i;
	double min = 0;
	for(i=0;i<length;i++){
		if(*(array+i) < min){
			min = *(array+i);
		}
	}
	return min;
}

//求最大值
double getMax(double *array,int length){
	int i;
	double min = 0;
	for(i=0;i<length;i++){
		if(*(array+i) > min){
			min = *(array+i);
		}
	}
	return min;
}

//求和
double getSum(double *array,int length){
	int i;
	double sum = 0;
	for(i=0;i<length;i++){
		sum += *(array+i);
	}
	return sum;
}

//求平均值
double getMean(double *array,int length){
	if(length > 0){
		double mean = getSum(array,length);
		mean /= length;
		return mean;
	}else{
		return 0;
	}
}

//求加权平均值,array和weights长度必须相等
double getAverage(double *array,double *weights,int length){
	int i;
	double weightsum = getSum(weights,length);
	double average = 0;
	for(i=0;i<length;i++){
		average += *(array + i) * *(weights + i);
	}
	average /= weightsum;
	return average;
}

//求方差
double getVariance(double *array,int length){
	if(length > 0){
		int i;
		double sum = 0;
		double mean = getMean(array,length);
		for(i=0;i<length;i++){
			sum += pow(*(array + i) - mean,2);
		}
		return sum / length;
	}else{
		return 0;
	}
}

//求标准差
double getStandardDeviation(double *array,int length){
	if(length > 0){
		return sqrt(getVariance(array,length));
	}else{
		return 0;
	}
}

//对0的个数计数
int countZero(double *array,int length){
	int i,num = 0;
	for(i=0;i<length;i++){
		if(*(array+i) == 0){
			num++;
		}
	}
	return num;
}

//将double分成整数和小数两个部分
void splitDouble(double num,int *intPart,double *floatPart){
	*intPart = (int)num;
	*floatPart = num - *intPart;
}

//double转为int，四舍五入
void doubleToIntAround(double num,int *toInt){
	*toInt = (int)num;
	if(num - *toInt >= 0.5) *toInt += 1;
}

