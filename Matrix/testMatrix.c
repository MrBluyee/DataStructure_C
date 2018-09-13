#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int a[]={0,0,4,4};
	int b[]={0,0,2,8};
	int c[]={0,0,0,16};
	int d[]={0,2,2,4};
	int e[]={2,2,2,2};
	
	double data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	double elem;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrixFromDatas(data,16,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	printf("Matrix Trace = %g\n",getSecondOrderMatrixTrace(m));
	getMatrixElem(m,0,0,2,1,&elem);
	printf("Elem m[2][1] = %g\n",elem);

	m2 = getSecondOrderMatrixRows(m,1,3);
	printf("get rows:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	destroyMatrix(m2);
	m2 = getSecondOrderMatrixColumes(m,1,3);
	printf("get columes:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	destroyMatrix(m2);
	m2 = getSecondOrderSubMatrix(m,1,1,3,3);
	printf("get sub matrix:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	kMulMatrix(m,2);
	printf("m shape : ");
	printShape(m);
	printarray(m);
	printf("\n");
	
	destroyMatrix(m2);
	m2 = copyMatrix(m);
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	swapSecondOrderMatrixColume(m2,1,2);
	printf("swap Colume m2:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	kMulSecondOrderMatrixRow(m2,2,1.7);
	printf("1.7 * m2 row2:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");	
	
	kMulSecondOrderMatrixColume(m2,1,0.3);
	printf("0.3 * m2 colume1:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	spliceSecondOrderMatrixRow(m2,m);
	printf("row append m to m2:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	deleteSecondOrderMatrixRows(m2,1,5);
	printf("delete m2 row 1,5:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	spliceSecondOrderMatrixColume(m2,m);
	printf("Colume append m to m2:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	m3 = mulSecondOrderMatrixs(m,m2);
	printf("m3 =  m X m2:\n");
	printf("m3 shape : ");
	printShape(m3);
	printarray(m3);
	printf("\n");	
	
	deleteSecondOrderMatrixColumes(m2,2,4);
	printf("delete m2 columes 2,3:\n");
	printf("m2 shape : ");
	printShape(m2);
	printarray(m2);
	printf("\n");
	
	initDshape(&dshape,b);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,0,1,&elem);
	printf("Elem m[0][1] = %g\n",elem);
	printf("\n");
	
	transposeSecondOrderMatrix(m);
	printf("transpose m:\n");
	printShape(m);
	printarray(m);
	printf("\n");
	
	swapSecondOrderMatrixRow(m,1,2);
	printf("swap row m:\n");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,0,1,&elem);
	printf("Elem m[0][1] = %g\n",elem);
	printf("\n");
	
	initDshape(&dshape,c);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,0,7,&elem);
	printf("Elem m[7] = %g\n",elem);
	printf("\n");
	
	transposeSecondOrderMatrix(m);
	printf("transpose m:\n");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,0,2,0,&elem);
	printf("Elem m[2][0] = %g\n",elem);
	printf("\n");
	
	initDshape(&dshape,d);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,0,1,0,3,&elem);
	printf("Elem m[1][0][3] = %g\n",elem);
	printf("\n");
	
	initDshape(&dshape,e);
	reshape(m,dshape);
	printf("shape : ");
	printShape(m);
	printarray(m);
	getMatrixElem(m,1,0,1,1,&elem);
	printf("Elem m[1][0][1][1] = %g\n",elem);
	printf("\n");
	
	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
