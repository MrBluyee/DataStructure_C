#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int rank = 0;
	double norm = 0;
	int a[]={0,0,4,5};
	int b[]={0,0,4,1};
	
	double data[] = {1,3,3,-2,1,2,6,1,-3,0,1,3,-2,-1,-1,3,9,4,-5,1};
	double data2[] = {3,2,-1,5};
	double elem;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrixFromDatas(data,20,dshape);
	printarray(m);
	printf("\n");

	initDshape(&dshape,b);
	m2 = creatMatrixFromDatas(data2,4,dshape);
	printarray(m2);
	printf("\n");

	m3 = solveNonHomoLinearEquations(m, m2);
	//m3 = solveHomoLinearEquations(m);
	printarray(m3);

	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
