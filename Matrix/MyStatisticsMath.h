/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MYSTATISTICSMATH_H
#define _MYSTATISTICSMATH_H
/* Exported types ------------------------------------------------------------*/

double getMin(double *array,int length);
double getMax(double *array,int length);
double getSum(double *array,int length);
double getMean(double *array,int length);
double getAverage(double *array,double *weights,int length);
double getVariance(double *array,int length);
double getStandardDeviation(double *array,int length);
int countZero(double *array,int length);
void splitDouble(double num,int *intPart,double *floatPart);
void doubleToIntAround(double num,int *toInt);

#endif

