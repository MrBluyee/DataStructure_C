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

typedef struct MatrixResult{
	double *array;  
	int length; //长度
}MatrixResult;

Matrix *creatAsMatrixFromDatas(double *data,int data_len, Dshape dshape);
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
int transposeSecondOrderMatrix(Matrix *m);
int swapSecondOrderMatrixRow(Matrix *m, int row1,int row2);
int swapSecondOrderMatrixColume(Matrix *m, int colume1,int colume2);
int kMulSecondOrderMatrixRow(Matrix *m, int row,double k);
int kMulSecondOrderMatrixColume(Matrix *m, int colume,double k);
int deleteSecondOrderMatrixRows(Matrix *m,int startRow,int endRow);
int deleteSecondOrderMatrixColumes(Matrix *m,int startColume,int endColume);
int deleteSecondOrderMatrixRowAndColume(Matrix *m,int row,int colume);
int spliceSecondOrderMatrixRow(Matrix *m1,Matrix *m2);
int spliceSecondOrderMatrixColume(Matrix *m1,Matrix *m2);
int kAddMatrix(Matrix *m,double k);
int kSubMatrix(Matrix *m,double k);
int kMulMatrix(Matrix *m,double k);
int kDivMatrix(Matrix *m,double k);
Matrix *addSecondOrderMatrixs(Matrix *m1,Matrix *m2);
Matrix *subSecondOrderMatrixs(Matrix *m1,Matrix *m2);
Matrix *dotSecondOrderMatrixs(Matrix *m1,Matrix *m2);
Matrix *mulSecondOrderMatrixs(Matrix *m1,Matrix *m2);
int detSecondOrderMatrixs(Matrix *m,double *result);
void destroyMatrix(Matrix *m);

#endif