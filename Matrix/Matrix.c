#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

//从连续的数据创建数组,浅拷贝
Matrix *creatAsMatrixFromDatas(double *data,int data_len, Dshape dshape){
	int i = 0; 
	if(!data) return NULL;
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	m->array = data;
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

//从连续的数据创建数组,深拷贝
Matrix *creatMatrixFromDatas(double *data,int data_len, Dshape dshape){
	int i = 0; 
	if(!data) return NULL;
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	m->array = (double *)malloc(data_len*sizeof(double));
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
	m->array = (double *)malloc(data_len*sizeof(double));
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
	m->array = (double *)malloc(data_len*sizeof(double));
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
	m->array = (double *)malloc(data_len*sizeof(double));
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
	if(dshape.shape[0] != 0 || dshape.shape[1] != 0 || 
	dshape.shape[2] <= 1 || dshape.shape[2] != dshape.shape[3]) return NULL;//dshape不是二维方阵
	int i = 0,data_len;
	data_len = dshape.shape[2] * dshape.shape[3];
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	m->array = (double *)malloc(data_len*sizeof(double));
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
	if(m){
		if(m->array){
			free(m->array);
			m->array = NULL;
		}
		free(m);
	}
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
	if(m->length > 0){
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
			printf("%g",*(m->array + i));
		}
		for(i=0;i<4;i++){
			if(m->dshape.shape[i] != 0){
				printf("]");
			}
		}
	}
	printf("\n");
}

//求二维方阵数组的迹
double getSecondOrderMatrixTrace(Matrix *m){
	double result = 0;
	int i;
	if(!m) return -1;
	if(m->dshape.shape[0] != 0 || m->dshape.shape[1] != 0 || 
	m->dshape.shape[2] == 0) return 0; //非二阶矩阵
	if(m->dshape.shape[2] != m->dshape.shape[3]) return 0; //非方阵
	for(i=0;i<m->dshape.shape[2];i++){
		result += *(m->array + i*m->dshape.shape[2] + i);
	}
	return result;
}

//在二维数组m1的行末尾按行拼接上m2，要求行的长度要一致
int spliceSecondOrderMatrixRow(Matrix *m1,Matrix *m2){
	int i;
	if(!m1 || !m2) return -1;
	if(m1->dshape.shape[3] != m2->dshape.shape[3]) return -1;
	m1->array = (double *)realloc(m1->array,(m1->length+m2->length)*sizeof(double));
	if(!m1->array) return -1;
	for(i=0;i<m2->length;i++){
		*(m1->array + m1->length + i) = *(m2->array + i);
	}
	if(m1->dshape.shape[2] == 0){
		if(m2->dshape.shape[2] == 0){
			m1->dshape.shape[2] = 2;
		}else{
			m1->dshape.shape[2] = 1 + m2->dshape.shape[2];
		}
	}else{
		if(m2->dshape.shape[2] == 0){
			m1->dshape.shape[2] += 1;
		}else{
			m1->dshape.shape[2] += m2->dshape.shape[2];
		}
	}
	m1->size = m1->length+m2->length;
	m1->length += m2->length;
	return 0;
}

//在二维数组m1的列末尾按列拼接上m2，要求列的长度要一致
int spliceSecondOrderMatrixColume(Matrix *m1,Matrix *m2){
	if(transposeSecondOrderMatrix(m1) == -1) return -1;
	if(transposeSecondOrderMatrix(m2) == -1) return -1;
	if(spliceSecondOrderMatrixRow(m1,m2) == -1)return -1;
	if(transposeSecondOrderMatrix(m1) == -1) return -1;
	if(transposeSecondOrderMatrix(m2) == -1) return -1;
	return 0;
}

//获得数组的元素
int getMatrixElem(Matrix *m,int dimen0,int dimen1,int dimen2,int dimen3,double *elem){
	int w,x,y,z,index;
	if(!m) return -1;
	if((dimen0 != 0 && m->dshape.shape[0] == 0) || 
	(dimen1 != 0 && m->dshape.shape[1] == 0)) return -1;
	if((dimen2 != 0 && m->dshape.shape[2] == 0) || 
	dimen3 >= m->dshape.shape[3]) return -1;
	if(dimen0 > m->dshape.shape[0] || dimen1 > m->dshape.shape[1] || 
	dimen2 > m->dshape.shape[2]) return -1;
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
	if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && 
	m->dshape.shape[2] == 0 && m->dshape.shape[3] != 0){
		if(startRow != 0 || endRow != 1) return NULL;
		subm = copyMatrix(m);
	}else if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && 
	m->dshape.shape[2] != 0 && m->dshape.shape[3] != 0){
		if(startRow < 0 || startRow >= m->dshape.shape[2] || 
		endRow > m->dshape.shape[2] || endRow < startRow) return NULL;
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
	if(startColume >= 0 && startColume < m->dshape.shape[3] && 
	endColume <= m->dshape.shape[3] && endColume > startColume){
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
	if(!m1) return NULL;
	m2 = getSecondOrderMatrixColumes(m1,startColume,endColume);
	destroyMatrix(m1);
	return m2;
}

//转置二维数组
int transposeSecondOrderMatrix(Matrix *m){
	int i,j,k=0;
	if(!m) return -1;
	Matrix *m1 = copyMatrix(m);
	if(m1->dshape.shape[2] != 0){ //二维数组
		m->dshape.shape[2] = m1->dshape.shape[3];
		m->dshape.shape[3] = m1->dshape.shape[2];
		for(i=0;i<m1->dshape.shape[3];i++){
			for(j=0;j<m1->dshape.shape[2];j++){
				*(m->array+k) = *(m1->array+j*m1->dshape.shape[3]+i);
				k++;
			}
		}
	}else{ //一维数组
		m->dshape.shape[2] = m1->dshape.shape[3];
		m->dshape.shape[3] = 1;
	}
	destroyMatrix(m1);
	return 0;
}

//交换二维数组的两行
int swapSecondOrderMatrixRow(Matrix *m, int row1,int row2){
	int i;
	if(!m) return -1;
	if(row1 == row2 || m->dshape.shape[2] == 0) return -1;
	if(row1 < 0 || row1 >= m->dshape.shape[2] || 
	row2 < 0 || row2 >= m->dshape.shape[2]) return -1;
	double temp; 
	for(i=0;i<m->dshape.shape[3];i++){
		temp = *(m->array+row1*m->dshape.shape[3]+i);
		*(m->array+row1*m->dshape.shape[3]+i) = *(m->array+row2*m->dshape.shape[3]+i);
		*(m->array+row2*m->dshape.shape[3]+i) = temp;
	}
	return 0;
}

//交换二维数组的两列
int swapSecondOrderMatrixColume(Matrix *m, int colume1,int colume2){
	int i;
	if(!m) return -1;
	if(colume1 == colume2) return -1;
	if(colume1 < 0 || colume1 >= m->dshape.shape[3] || 
	colume2 < 0 || colume2 >= m->dshape.shape[3]) return -1;
	double temp; 
	for(i=0;i<m->length/m->dshape.shape[3];i++){
		temp = *(m->array+i*m->dshape.shape[3]+colume1);
		*(m->array+i*m->dshape.shape[3]+colume1) = *(m->array+i*m->dshape.shape[3]+colume2);
		*(m->array+i*m->dshape.shape[3]+colume2) = temp;
	}
	return 0;
}

//二维数组的其中一行乘上一个系数
int kMulSecondOrderMatrixRow(Matrix *m, int row,double k){
	int i;
	if(!m) return -1;
	if(m->dshape.shape[2] == 0){//一维数组
		if(row != 0) return -1;
		for(i=0;i<m->dshape.shape[3];i++){
			*(m->array+i) *= k;
		}
	}else{
		if(row < 0 || row >= m->dshape.shape[2]) return -1;
		for(i=0;i<m->dshape.shape[3];i++){
			*(m->array+row*m->dshape.shape[3]+i) *= k;
		}
	}
	return 0;
}

//二维数组的其中一列乘上一个系数
int kMulSecondOrderMatrixColume(Matrix *m, int colume,double k){
	int i;
	if(!m) return -1;
	if(colume < 0 || colume >= m->dshape.shape[3]) return -1;
	for(i=0;i<m->length/m->dshape.shape[3];i++){
		*(m->array+i*m->dshape.shape[3]+colume) *= k;
	}
	return 0;
}

//删除二维数组的连续几行
int deleteSecondOrderMatrixRows(Matrix *m,int startRow,int endRow){
	int i = 0;
	if(!m) return -1;
	if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && 
	m->dshape.shape[2] == 0 && m->dshape.shape[3] != 0){
		if(startRow != 0 || endRow != 1) return -1;
		clearMatrix(m);
	}else if(m->dshape.shape[0] == 0 && m->dshape.shape[1] == 0 && 
	m->dshape.shape[2] != 0 && m->dshape.shape[3] != 0){
		if(startRow < 0 || startRow >= m->dshape.shape[2] || 
		endRow > m->dshape.shape[2] || endRow < startRow) return -1;
		for(i=0;i<m->length-endRow*m->dshape.shape[3];i++){
			*(m->array+startRow*m->dshape.shape[3]+i) = *(m->array+endRow*m->dshape.shape[3]+i);
		}
		m->dshape.shape[2] -= (endRow - startRow);
		if(m->dshape.shape[2] == 1){ //只剩1行，变为一维数组
			m->dshape.shape[2] = 0;
		}
		m->length -= (endRow - startRow)*m->dshape.shape[3];
	}
	return 0;
}

//删除二维数组的连续几列
int deleteSecondOrderMatrixColumes(Matrix *m,int startColume,int endColume){
	if(transposeSecondOrderMatrix(m) == -1) return -1;
	if(deleteSecondOrderMatrixRows(m,startColume,endColume) == -1) return -1;
	return transposeSecondOrderMatrix(m);
}

//删除二维数组的指定的行和列
int deleteSecondOrderMatrixRowAndColume(Matrix *m,int row,int colume){
	if(deleteSecondOrderMatrixColumes(m,colume,colume + 1) == -1) return -1;
	if(deleteSecondOrderMatrixRows(m,row,row + 1) == -1) return -1;
	return 0;
}

//求解数组加上一个系数
int kAddMatrix(Matrix *m,double k){
	int i;
	if(!m) return -1;
	for(i=0;i<m->length;i++){
		*(m->array+i) += k;
	}
	return 0;
}

//两个二维数组相加，m1,m2的维数必须相同
Matrix *addSecondOrderMatrixs(Matrix *m1,Matrix *m2){
	int i = 0;
	if(!m1 || !m2) return NULL;
	if(m1->dshape.shape[2] != m2->dshape.shape[2] || m1->dshape.shape[3] != m2->dshape.shape[3]) return NULL;
	if(m1->length != m2->length) return NULL;
	Matrix *resultm = (Matrix *)malloc(sizeof(Matrix));
	if(!resultm) return NULL;
	resultm->size = m1->length;
	resultm->length = resultm->size;
	resultm->array = (double *)malloc(resultm->size*sizeof(double));
	if(!resultm->array){
		free(resultm);
		return NULL;
	}
	for(i=0;i<resultm->length;i++){
		*(resultm->array + i) = *(m1->array + i) + *(m2->array + i);
	}
	resultm->dshape.shape[0] = 0;
	resultm->dshape.shape[1] = 0;
	resultm->dshape.shape[2] = m1->dshape.shape[2];
	resultm->dshape.shape[3] = m1->dshape.shape[3];
	return resultm;
}

//求解数组减去一个系数
int kSubMatrix(Matrix *m,double k){
	int i;
	if(!m) return -1;
	for(i=0;i<m->length;i++){
		*(m->array+i) -= k;
	}
	return 0;
}

//两个二维数组相减，m1-m2，m1,m2的维数必须相同
Matrix *subSecondOrderMatrixs(Matrix *m1,Matrix *m2){
	int i = 0;
	if(!m1 || !m2) return NULL;
	if(m1->dshape.shape[2] != m2->dshape.shape[2] || m1->dshape.shape[3] != m2->dshape.shape[3]) return NULL;
	if(m1->length != m2->length) return NULL;
	Matrix *resultm = (Matrix *)malloc(sizeof(Matrix));
	if(!resultm) return NULL;
	resultm->size = m1->length;
	resultm->length = resultm->size;
	resultm->array = (double *)malloc(resultm->size*sizeof(double));
	if(!resultm->array){
		free(resultm);
		return NULL;
	}
	for(i=0;i<resultm->length;i++){
		*(resultm->array + i) = *(m1->array + i) - *(m2->array + i);
	}
	resultm->dshape.shape[0] = 0;
	resultm->dshape.shape[1] = 0;
	resultm->dshape.shape[2] = m1->dshape.shape[2];
	resultm->dshape.shape[3] = m1->dshape.shape[3];
	return resultm;
}

//两个二维数组点积,对应元素相乘,m1,m2的维数必须相同
Matrix *dotSecondOrderMatrixs(Matrix *m1,Matrix *m2){
	int i = 0;
	if(!m1 || !m2) return NULL;
	if(m1->dshape.shape[2] != m2->dshape.shape[2] || m1->dshape.shape[3] != m2->dshape.shape[3]) return NULL;
	if(m1->length != m2->length) return NULL;
	Matrix *resultm = (Matrix *)malloc(sizeof(Matrix));
	if(!resultm) return NULL;
	resultm->size = m1->length;
	resultm->length = resultm->size;
	resultm->array = (double *)malloc(resultm->size*sizeof(double));
	if(!resultm->array){
		free(resultm);
		return NULL;
	}
	for(i=0;i<resultm->length;i++){
		*(resultm->array + i) = *(m1->array + i) * *(m2->array + i);
	}
	resultm->dshape.shape[0] = 0;
	resultm->dshape.shape[1] = 0;
	resultm->dshape.shape[2] = m1->dshape.shape[2];
	resultm->dshape.shape[3] = m1->dshape.shape[3];
	return resultm;
}

//求解数组除以一个系数
int kDivMatrix(Matrix *m,double k){
	int i;
	if(!m) return -1;
	for(i=0;i<m->length;i++){
		*(m->array+i) /= k;
	}
	return 0;
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

//两个二维数组的矩阵积，m1为m X n矩阵，m2为n X p矩阵，乘积返回一个m X p矩阵
Matrix *mulSecondOrderMatrixs(Matrix *m1,Matrix *m2){
	int i,j,k,count=0;
	double temp = 0;
	if(!m1 || !m2) return NULL;
	if(m2->dshape.shape[2] == 0) m2->dshape.shape[2] = 1; //考虑1维数组情况
	if(m1->dshape.shape[3] != m2->dshape.shape[2]){  //矩阵不匹配
		if(m2->dshape.shape[2] == 1) m2->dshape.shape[2] = 0;
		return NULL;
	}
	Matrix *resultm = (Matrix *)malloc(sizeof(Matrix));
	if(!resultm) return NULL;
	if(m1->dshape.shape[2] == 0) m1->dshape.shape[2] = 1; //考虑1维数组情况
	resultm->size = m1->dshape.shape[2] * m2->dshape.shape[3];
	resultm->length = resultm->size;
	resultm->array = (double *)malloc(resultm->size*sizeof(double));
	if(!resultm->array){
		free(resultm);
		if(m2->dshape.shape[2] == 1) m2->dshape.shape[2] = 0;
		if(m1->dshape.shape[2] == 1) m1->dshape.shape[2] = 0;
		return NULL;
	}
	for(i=0;i<m1->dshape.shape[2];i++){
		for(j=0;j<m2->dshape.shape[3];j++){
			temp = 0;
			for(k=0;k<m1->dshape.shape[3];k++){
				temp += *(m1->array + i*m1->dshape.shape[3]+ k) * *(m2->array + k*m2->dshape.shape[3] + j);
			}
			*(resultm->array + count) = temp;
			count++;
		}
	}
	resultm->dshape.shape[0] = 0;
	resultm->dshape.shape[1] = 0;
	if(m2->dshape.shape[2] == 1) m2->dshape.shape[2] = 0;
	if(m1->dshape.shape[2] == 1){
		m1->dshape.shape[2] = 0;
		resultm->dshape.shape[2] = 0;
	}
	resultm->dshape.shape[3] = m2->dshape.shape[3];
	return resultm;
}

//使用定义求n阶数组的行列式，要求m为n阶二维方阵，n>=2
static double DetSecondOrderMatrixs(Matrix *m){
	if(!m) return -1;
	if(m->dshape.shape[0] != 0 || m->dshape.shape[1] != 0 || 
	m->dshape.shape[2] != m->dshape.shape[3] || m->dshape.shape[3] < 2) return -1;
	printarray(m);
	if(m->dshape.shape[3] == 2){
		//递归到一个二维矩阵时可以直接求解行列式
		return *(m->array + 0*m->dshape.shape[2] + 0) * *(m->array + 1*m->dshape.shape[2] + 1) -
		*(m->array + 0*m->dshape.shape[2] + 1) * *(m->array + 1*m->dshape.shape[2] + 0);
	}else{
		double res = 0;
		int i;
		for(i=0;i<m->dshape.shape[2];i++){//为方便编程，每次都由第一行展开
			int k = 1;
			if(i % 2 == 1){
				k = -1;
			}
			deleteSecondOrderMatrixRowAndColume(m,1,i + 1);
			res += *(m->array + i) * k * DetSecondOrderMatrixs(m);
		}
		return res;
	}
}

//求行列式，保护传入数组m
int detSecondOrderMatrixs(Matrix *m,double *result){
	Matrix *copym = NULL;
	copym = copyMatrix(m);
	if(!copym) return -1;
	*result = DetSecondOrderMatrixs(copym);
	destroyMatrix(copym);
	return 0;
}

//求解线性矩阵方程
Matrix *solveSecondOrderMatrixs(Matrix *m){
	
}

//寻找矩阵的乘法逆矩阵
Matrix *invSecondOrderMatrixs(Matrix *m){
	
}