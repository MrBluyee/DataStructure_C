#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int a[]={0,0,3,3};

	double data[] = {1,2,3,3,4,6,4,6,5};
	double elem;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrixFromDatas(data,9,dshape);
	printf("m shape: ");
	printShape(m);
	printarray(m);
	printf("m Trace = %g\n",getSecondOrderMatrixTrace(m));
	getMatrixElem(m,0,0,2,1,&elem);
	printf("Elem m[2][1] = %g\n",elem);
	detSecondOrderMatrixs(m,&elem);
	printf("m determinant = %g\n",elem);
	printf("\n");
	
	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
