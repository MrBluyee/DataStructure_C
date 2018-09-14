#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int rank = 0;
	double norm = 0;
	int a[]={0,0,2,3};
	int b[]={0,0,4,3};
	
	//double data[] = {1,2,3,3,4,6,4,6,5};
	double data[] = {-1,2,-3,4,-6,6};
	double elem;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrixFromDatas(data,6,dshape);
	
	norm = getMatrixInfNorm(m);
	printf("m Inf norm = %g\n",norm);
	norm = getMatrixL0Norm(m);
	printf("m L0 norm = %g\n",norm);
	norm = getMatrixL1Norm(m);
	printf("m L1 norm = %g\n",norm);
	norm = getMatrixL2Norm(m);
	printf("m L2 norm = %g\n",norm);
	norm = getMatrixL21Norm(m);
	printf("m L21 norm = %g\n",norm);
	
	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
