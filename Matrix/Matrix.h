/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MATRIX_H
#define _MATRIX_H
/* Exported types ------------------------------------------------------------*/

typedef enum Dtype{
	d_uchar,
	d_char,
	d_int,
	d_uint,
	d_float,
	d_double
}Dtype;

typedef struct Dshape{
	int shape[4]; //最多四维
}Dshape;

typedef struct Matrix{
	void *array;  
	Dtype dtype;
	Dshape dshape;
	int length; //长度
	int size; //空间大小
}Matrix;

Matrix *creatMatrix(void *data,int data_len, Dtype dtype, Dshape dshape);
void initDshape(Dshape *dshape,int *shapeval);
int reshape(Matrix *m,Dshape dshape);
void clearMatrix(Matrix *m);
void printShape(Matrix *m);
void printarray(Matrix *m);
double getSecondOrderMatrixTrace(Matrix *m);
int getMatrixElem(Matrix *m,int dimen0,int dimen1,int dimen2,int dimen3,void *elem);
Matrix *copyMatrix(Matrix *m);
Matrix *getMatrixRows(Matrix *m,int startRow,int endRow);
void destroyMatrix(Matrix *m);

#endif