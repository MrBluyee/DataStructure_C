#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

//从连续的数据创建数组
Matrix *creatMatrixFromDatas(double *data,int data_len, Dshape dshape){
	int i = 0; 
	if(!data) return NULL;
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	m->array = (double *)malloc(data_len*sizeof(double));
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	for(i=0;i<data_len;i++){
		*(m->array+i) = *(data+i);
	}
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

//创建单值数组
Matrix *creatMatrixFromValue(double value, Dshape dshape){
	int i = 0,w,x,y,z,data_len; 
	z = dshape.shape[3];
	y = dshape.shape[2] * z;
	x = dshape.shape[1] * y;
	w = dshape.shape[0] * x;
	if(w != 0){
		data_len = w;
	}else if(x != 0){
		data_len = x;
	}else if(y != 0){
		data_len = y;
	}else if(z != 0){
		data_len = z;
	}
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	switch(dtype){
		m->array = (double *)malloc(data_len*sizeof(double));
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	for(i=0;i<data_len;i++){
		*(m->array+i) = value;
	}
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

//指定步长，创建等间隔值的数组
Matrix *creatMatrixFromArange(double startVal, double stepVal,Dshape dshape){
	int i = 0,w,x,y,z,data_len; 
	z = dshape.shape[3];
	y = dshape.shape[2] * z;
	x = dshape.shape[1] * y;
	w = dshape.shape[0] * x;
	if(w != 0){
		data_len = w;
	}else if(x != 0){
		data_len = x;
	}else if(y != 0){
		data_len = y;
	}else if(z != 0){
		data_len = z;
	}
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	switch(dtype){
		m->array = (double *)malloc(data_len*sizeof(double));
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	for(i=0;i<data_len;i++){
		*(m->array+i) = startVal + stepVal * i;
	}
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

//指定范围之间的均匀间隔数量，创建等间隔值的数组
Matrix *creatMatrixFromLinspace(double startVal, double endVal,Dshape dshape){
	int i = 0,w,x,y,z,data_len;
	double stepVal;
	z = dshape.shape[3];
	y = dshape.shape[2] * z;
	x = dshape.shape[1] * y;
	w = dshape.shape[0] * x;
	if(w != 0){
		data_len = w;
	}else if(x != 0){
		data_len = x;
	}else if(y != 0){
		data_len = y;
	}else if(z != 0){
		data_len = z;
	}
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	switch(dtype){
		m->array = (double *)malloc(data_len*sizeof(double));
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	stepVal = (endVal - startVal) / data_len;
	for(i=0;i<data_len;i++){
		*(m->array+i) = startVal + stepVal * i;
	}
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

	
//创建全0数组
Matrix *creatZerosMatrix(Dshape dshape){
	return creatMatrixFromValue(0, dshape);
}

//创建全1数组
Matrix *creatOnesMatrix(Dshape dshape){
	return creatMatrixFromValue(1, dshape);
}

//创建二维单位阵
Matrix *creatIdentitySecondOrderMatrix(Dshape dshape){
	if(dshape.shape[0] != 0 || dshape.shape[1] != 0 || dshape.shape[2] <= 1 || dshape.shape[2] != dshape.shape[3]) return NULL;//dshape不是二维方阵
	int i = 0,data_len;
	data_len = dshape.shape[2] * dshape.shape[3];
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	switch(dtype){
		m->array = (double *)malloc(data_len*sizeof(double));
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	for(i=0;i<data_len;i++){
		*(m->array+i) = 0;
	}
	for(i=0;i<dshape.shape[3];i++){
		*(m->array+i*dshape.shape[3] + i) = 1;
	}
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

//数组的shape初始化
void initDshape(Dshape *dshape,int *shapeval){
	int i;
	if(!dshape) return;
	for(i=0;i<4;i++){
		dshape->shape[i] = *(shapeval+i);
	}
}

//清空数组，保留空间
void clearMatrix(Matrix *m){
	if(!m) return;
	m->length = 0;
}

//删除数组，并释放空间
void destroyMatrix(Matrix *m){
	free(m->array);
	m->array = NULL;
	free(m);
	m = NULL;
}

//重新调整数组shape
int reshape(Matrix *m,Dshape dshape){
	if(!m) return -1;
	m->dshape = dshape;
	return 0;
}

//打印数组shape
void printShape(Matrix *m){
	int i = 0,j;
	if(!m) return;
	printf("(");
	while(m->dshape.shape[i] == 0){
		i++;
	}
	printf("%d",m->dshape.shape[i]);
	i++;
	for(j=i;j<4;j++){
		printf(", %d",m->dshape.shape[j]);
	}
	printf(")\n");
}

//获得数组的维数，最多4维
int getMatrixNdim(Matrix *m){
	int i,ndim = 0;
	for(i=0;i<4;i++){
		if(m->dshape.shape[i] != 0){
			ndim ++;
		}
	}
	return ndim;
}

//打印数组
void printarray(Matrix *m){
	int i,w,x,y,z;
	if(!m) return;
	z = m->dshape.shape[3];
	y = m->dshape.shape[2] * z;
	x = m->dshape.shape[1] * y;
	w = m->dshape.shape[0] * x;
	for(i=0;i<3;i++){
		if(m->dshape.shape[i] != 0){
			printf("[");
		}
	}
	for(i=0;i<m->length;i++){
		if(i%z == 0){
			if(i == 0){
				printf("[");
			}else{
				if(x != 0){
					if(i%x == 0){
						printf("]]]\n[[[");
					}else if(i%y == 0){
						printf("]]\n[[");
					}else{
						printf("], [");
					}	
				}else if(y != 0){
					if(i%y == 0){
						printf("]]\n[[");
					}else{
						printf("]\n[");
					}
				}
			}
		}else{
			printf(", ");
		}
		printf("%f",*(m->array + i));
		}
	}
	for(i=0;i<4;i++){
		if(m->dshape.shape[i] != 0){
			printf("]");
		}
	}
	printf("\n");
}

//求二维方阵数组的迹
double getSecondOrderMatrixTrace(Matrix *m){
	double result = 0;
	int i;
	if(!m) return -1;
	if(m->dshape.shape[0] != 0 || m->dshape.shape[1] != 0 || m->dshape.shape[2] == 0) return 0; //非二阶矩阵
	if(m->dshape.shape[2] != m->dshape.shape[3]) return 0; //非方阵
	for(i=0;i<m->dshape.shape[2];i++){
		result += *(m->array + i*m->dshape.shape[2] + i);
	}
	return result;
}

//获得数组的元素
int getMatrixElem(Matrix *m,int dimen0,int dimen1,int dimen2,int dimen3,double *elem){
	int w,x,y,z,index;
	if(!m) return -1;
	if((dimen0 != 0 && m->dshape.shape[0] == 0) || (dimen1 != 0 && m->dshape.shape[1] == 0)) return -1;
	if((dimen2 != 0 && m->dshape.shape[2] == 0) || dimen3 >= m->dshape.shape[3]) return -1;
	if(dimen0 > m->dshape.shape[0] || dimen1 > m->dshape.shape[1] || dimen2 > m->dshape.shape[2]) return -1;
	if(dimen0 < 0 || dimen1 < 0 || dimen2 < 0 || dimen3 < 0)return -1;
	z = m->dshape.shape[3];
	y = m->dshape.shape[2] * z;
	x = m->dshape.shape[1] * y;
	w = m->dshape.shape[0] * x;
	index = dimen0*x + dimen1*y + dimen2*z + dimen3;
	*elem = *(m->array + index);
	return 0;
}

//复制数组
Matrix *copyMatrix(Matrix *m){
	int i = 0;
	if(!m) return NULL;
	Matrix *copym = (Matrix *)malloc(sizeof(Matrix));
	if(!copym) return NULL;
	copym->dshape = m->dshape;
	copym->length = m->length;
	copym->size = m->length;
	copym->array = (double *)malloc(copym->length*sizeof(double));
	if(!copym->array){
		free(copym);
		return NULL;
	}
	for(i=0;i<copym->length;i++){
		*(copym->array+i) = *(m->array+i);
	}
	return copym;
}

//提取二维数组的连续多行，返回一个包含多行内容的子数组
Matrix *getSecondOrderMatrixRows(Matrix *m,int startRow,int endRow){
	int i = 0;
	if(!m) return NULL;
	Matrix *subm = NULL;
	if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && m->dshape.shape[2] == 0 && m->dshape.shape[3] != 0){
		if(startRow != 0 || endRow != 1) return NULL;
		printf("hello\n");
		subm = copyMatrix(m);
	}else if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && m->dshape.shape[2] != 0 && m->dshape.shape[3] != 0){
		if(startRow < 0 || startRow >= m->dshape.shape[2] || endRow > m->dshape.shape[2] || endRow < startRow) return NULL;
		subm = (Matrix *)malloc(sizeof(Matrix));
		if(!subm) return NULL;
		if(endRow - startRow == 1){
			subm->dshape.shape[0] = 0;
			subm->dshape.shape[1] = 0;
			subm->dshape.shape[2] = 0;
			subm->dshape.shape[3] = m->dshape.shape[3];
		}else{
			subm->dshape.shape[0] = 0;
			subm->dshape.shape[1] = 0;
			subm->dshape.shape[2] = endRow - startRow;
			subm->dshape.shape[3] = m->dshape.shape[3];
		}
		subm->length = (endRow - startRow)*m->dshape.shape[3];
		subm->size = subm->length;
		subm->array = (double *)malloc(subm->length*sizeof(double));
		if(!subm->array){
			free(subm);
			return NULL;
		}
		for(i=0;i<subm->length;i++){
			*(subm->array+i) = *(m->array+startRow*m->dshape.shape[3]+i);
		}
	}
	return subm;
}

//提取二维数组的连续多列，返回一个包含多列内容的子数组
Matrix *getSecondOrderMatrixColumes(Matrix *m,int startColume,int endColume){
	int i = 0,j,w,x,y,z;
	if(!m) return NULL;
	Matrix *subm = NULL;
	if(startColume >= 0 || startColume < m->dshape.shape[3] || endColume <= m->dshape.shape[3] || endColume > startColume){
		subm = (Matrix *)malloc(sizeof(Matrix));
		if(!subm) return NULL;
		subm->dshape.shape[0] = m->dshape.shape[0];
		subm->dshape.shape[1] = m->dshape.shape[1];
		subm->dshape.shape[2] = m->dshape.shape[2];
		subm->dshape.shape[3] = endColume - startColume;
		z = subm->dshape.shape[3];
		y = z*subm->dshape.shape[2];
		x = y*subm->dshape.shape[1];
		w = x*subm->dshape.shape[0];
		if(w != 0){
			subm->length = w;
		}else if(x != 0){
			subm->length = x;
		}else if(y != 0){
			subm->length = y;
		}else if(z != 0){
			subm->length = z;
		}
		subm->size = subm->length;
		subm->array = (double *)malloc(subm->length*sizeof(double));
		if(!subm->array){
			free(subm);
			return NULL;
		}
		for(i=0;i<subm->length/z;i++){
			for(j=0;j<subm->dshape.shape[3];j++){
				*(subm->array+i*z+j) = *(m->array+i*m->dshape.shape[3]+startColume+j);
			}
		}
	}
	return subm;
}

//从二维数组一个行与列下标为起点，获取其子数组
Matrix *getSecondOrderSubMatrix(Matrix *m,int startRow,int startColume,int endRow,int endColume){
	Matrix *m1 = NULL,*m2 = NULL;
	m1 = getSecondOrderMatrixRows(m,startRow,endRow);
	m2 = getSecondOrderMatrixColumes(m1,startColume,endColume);
	destroyMatrix(m1);
	return m2;
}

//求解数组乘一个系数
int kMulMatrix(Matrix *m,double k){
	int i;
	if(!m) return -1;
	for(i=0;i<m->length;i++){
		*(m->array+i) *= k;
	}
	return 0;
}



