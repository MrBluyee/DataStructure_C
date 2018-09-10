/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MATRIX_H
#define _MATRIX_H
/* Exported types ------------------------------------------------------------*/

typedef struct Dshape{
	int shape[4]; //最多四维
}Dshape;

typedef struct Matrix{
	double *array;  
	Dshape dshape; //数组结构
	int length; //长度
	int size; //空间大小
}Matrix;

Matrix *creatMatrixFromDatas(double *data,int data_len, Dshape dshape);
Matrix *creatMatrixFromValue(double value, Dshape dshape);
Matrix *creatMatrixFromArange(double startVal, double stepVal,Dshape dshape);
Matrix *creatMatrixFromLinspace(double startVal, double endVal,Dshape dshape);
Matrix *creatZerosMatrix(Dshape dshape);
Matrix *creatOnesMatrix(Dshape dshape);
Matrix *creatIdentitySecondOrderMatrix(Dshape dshape);
void initDshape(Dshape *dshape,int *shapeval);
int reshape(Matrix *m,Dshape dshape);
void clearMatrix(Matrix *m);
void printShape(Matrix *m);
int getMatrixNdim(Matrix *m);
void printarray(Matrix *m);
double getSecondOrderMatrixTrace(Matrix *m);
int getMatrixElem(Matrix *m,int dimen0,int dimen1,int dimen2,int dimen3,double *elem);
Matrix *copyMatrix(Matrix *m);
Matrix *getSecondOrderMatrixRows(Matrix *m,int startRow,int endRow);
Matrix *getSecondOrderMatrixColumes(Matrix *m,int startColume,int endColume);
Matrix *getSecondOrderSubMatrix(Matrix *m,int startRow,int startColume,int endRow,int endColume);
int kMulMatrix(Matrix *m,double k);
void destroyMatrix(Matrix *m);

#endif