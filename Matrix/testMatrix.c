#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	int a[]={0,0,4,4};
	int b[]={0,0,2,8};
	int c[]={0,0,0,16};
	int d[]={0,2,2,4};
	int e[]={2,2,2,2};
	
	int data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int elem;
	Dtype dtype = d_int;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrix(data,16,dtype,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	printf("Matrix Trace = %f\n",getSecondOrderMatrixTrace(m));
	getMatrixElem(m,0,0,2,1,&elem);
	printf("Elem m[2][1] = %d\n",elem);
	printf("\n");
	
	m2 = copyMatrix(m);
	printf("m2 shape : ");
	printShape(m);
	printarray(m);
	printf("\n");
	
	initDshape(&dshape,b);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,0,1,&elem);
	printf("Elem m[0][1] = %d\n",elem);
	printf("\n");
	
	initDshape(&dshape,c);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,0,7,&elem);
	printf("Elem m[7] = %d\n",elem);
	printf("\n");
	
	initDshape(&dshape,d);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,1,0,3,&elem);
	printf("Elem m[1][0][3] = %d\n",elem);
	printf("\n");
	
	initDshape(&dshape,e);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,1,0,1,1,&elem);
	printf("Elem m[1][0][1][1] = %d\n",elem);
	printf("\n");
	
	destroyMatrix(m);
	return 0;
}
