#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int rank = 0;
	int a[]={0,0,3,4};
	int b[]={0,0,4,3};
	
	//double data[] = {1,2,3,3,4,6,4,6,5};
	double data[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	double elem;
	Dshape dshape;
	initDshape(&dshape,b);
	
	m = creatMatrixFromDatas(data,12,dshape);
	
	getSecondOrderMatrixRank(m ,&rank);
	printf("m rank = %d\n",rank);
	
	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
