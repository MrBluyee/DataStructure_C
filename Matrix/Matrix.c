#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

Matrix *creatMatrix(void *data,int data_len, Dtype dtype, Dshape dshape){
	int i = 0; 
	if(!data) return NULL;
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	if(!m) return NULL;
	switch(dtype){
		case d_uchar:
			m->array = (unsigned char *)malloc(data_len*sizeof(unsigned char));
			break;
		case d_char:
			m->array = (char *)malloc(data_len*sizeof(char));
			break;
		case d_int:
			m->array = (int *)malloc(data_len*sizeof(int));
			break;
		case d_uint:
			m->array = (unsigned int *)malloc(data_len*sizeof(unsigned int));
			break;
		case d_float:
			m->array = (float *)malloc(data_len*sizeof(float));
			break;
		case d_double:
			m->array = (double *)malloc(data_len*sizeof(double));
			break;
	}
	if(!m->array){
		free(m);
		return NULL;
	}
	for(i=0;i<data_len;i++){
		switch(dtype){
			case d_uchar:
				*((unsigned char *)m->array+i) = *((unsigned char *)data+i);
				break;
			case d_char:
				*((char *)m->array+i) = *((char *)data+i);
				break;
			case d_int:
				*((int *)m->array+i) = *((int *)data+i);
				break;
			case d_uint:
				*((unsigned int *)m->array+i) = *((unsigned int *)data+i);
				break;
			case d_float:
				*((float *)m->array+i) = *((float *)data+i);
				break;
			case d_double:
				*((double *)m->array+i) = *((double *)data+i);
				break;
		}
	}
	m->dtype = dtype;
	m->dshape = dshape;
	m->length = data_len;
	m->size = data_len;
	return m;
}

void initDshape(Dshape *dshape,int *shapeval){
	int i;
	if(!dshape) return;
	for(i=0;i<4;i++){
		dshape->shape[i] = *(shapeval+i);
	}
}

void clearMatrix(Matrix *m){
	if(!m) return;
	m->length = 0;
}

void destroyMatrix(Matrix *m){
	free(m->array);
	m->array = NULL;
	free(m);
	m = NULL;
}

int reshape(Matrix *m,Dshape dshape){
	if(!m) return -1;
	m->dshape = dshape;
	return 0;
}

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
		switch(m->dtype){
			case d_uchar:
				printf("%c",*((unsigned char *)m->array + i));
				break;
			case d_char:
				printf("%c",*((char *)m->array + i));
				break;
			case d_int:
				printf("%d",*((int *)m->array + i));
				break;
			case d_uint:
				printf("%d",*((unsigned int *)m->array + i));
				break;
			case d_float:
				printf("%f",*((float *)m->array + i));
				break;
			case d_double:
				printf("%f",*((double *)m->array + i));
				break;
		}
	}
	for(i=0;i<4;i++){
		if(m->dshape.shape[i] != 0){
			printf("]");
		}
	}
	printf("\n");
}

double getSecondOrderMatrixTrace(Matrix *m){
	double result = 0;
	int i;
	if(!m) return -1;
	if(m->dshape.shape[0] != 0 || m->dshape.shape[1] != 0 || m->dshape.shape[2] == 0) return 0; //非二阶矩阵
	if(m->dshape.shape[2] != m->dshape.shape[3]) return 0; //非方阵
	for(i=0;i<m->dshape.shape[2];i++){
		switch(m->dtype){
			case d_uchar:
				result += *((unsigned char *)m->array + i*m->dshape.shape[2] + i);
				break;
			case d_char:
				result += *((char *)m->array + i*m->dshape.shape[2] + i);
				break;
			case d_int:
				result += *((int *)m->array + i*m->dshape.shape[2] + i);
				break;
			case d_uint:
				result += *((unsigned int *)m->array + i*m->dshape.shape[2] + i);
				break;
			case d_float:
				result += *((float *)m->array + i*m->dshape.shape[2] + i);
				break;
			case d_double:
				result += *((double *)m->array + i*m->dshape.shape[2] + i);
				break;
		}
	}
	return result;
}

int getMatrixElem(Matrix *m,int dimen0,int dimen1,int dimen2,int dimen3,void *elem){
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
	switch(m->dtype){
		case d_uchar:
			*((unsigned char *)elem) = *((unsigned char *)m->array + index);
			break;
		case d_char:
			*((char *)elem) = *((char *)m->array + index);
			break;
		case d_int:
			*((int *)elem) = *((int *)m->array + index);
			break;
		case d_uint:
			*((unsigned int *)elem) = *((unsigned int *)m->array + index);
			break;
		case d_float:
			*((float *)elem) = *((float *)m->array + index);
			break;
		case d_double:
			*((double *)elem) = *((double *)m->array + index);
			break;
	}
	return 0;
}

Matrix *copyMatrix(Matrix *m){
	int i = 0;
	if(!m) return NULL;
	Matrix *copym = (Matrix *)malloc(sizeof(Matrix));
	if(!copym) return NULL;
	copym->dtype = m->dtype;
	copym->dshape = m->dshape;
	copym->length = m->length;
	copym->size = m->length;
	switch(copym->dtype){
		case d_uchar:
			copym->array = (unsigned char *)malloc(copym->length*sizeof(unsigned char));
			break;
		case d_char:
			copym->array = (char *)malloc(copym->length*sizeof(char));
			break;
		case d_int:
			copym->array = (int *)malloc(copym->length*sizeof(int));
			break;
		case d_uint:
			copym->array = (unsigned int *)malloc(copym->length*sizeof(unsigned int));
			break;
		case d_float:
			copym->array = (float *)malloc(copym->length*sizeof(float));
			break;
		case d_double:
			copym->array = (double *)malloc(copym->length*sizeof(double));
			break;
	}
	if(!copym->array){
		free(copym);
		return NULL;
	}
	for(i=0;i<copym->length;i++){
		switch(copym->dtype){
			case d_uchar:
				*((unsigned char *)copym->array+i) = *((unsigned char *)m->array+i);
				break;
			case d_char:
				*((char *)copym->array+i) = *((char *)m->array+i);
				break;
			case d_int:
				*((int *)copym->array+i) = *((int *)m->array+i);
				break;
			case d_uint:
				*((unsigned int *)copym->array+i) = *((unsigned int *)m->array+i);
				break;
			case d_float:
				*((float *)copym->array+i) = *((float *)m->array+i);
				break;
			case d_double:
				*((double *)copym->array+i) = *((double *)m->array+i);
				break;
		}
	}
	return copym;
}

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
		subm->dtype = m->dtype;
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
		switch(m->dtype){
			case d_uchar:
				subm->array = (unsigned char *)malloc(subm->length*sizeof(unsigned char));
				break;
			case d_char:
				subm->array = (char *)malloc(subm->length*sizeof(char));
				break;
			case d_int:
				subm->array = (int *)malloc(subm->length*sizeof(int));
				break;
			case d_uint:
				subm->array = (unsigned int *)malloc(subm->length*sizeof(unsigned int));
				break;
			case d_float:
				subm->array = (float *)malloc(subm->length*sizeof(float));
				break;
			case d_double:
				subm->array = (double *)malloc(subm->length*sizeof(double));
				break;
		}
		if(!subm->array){
			free(subm);
			return NULL;
		}
		for(i=0;i<subm->length;i++){
			switch(subm->dtype){
				case d_uchar:
					*((unsigned char *)subm->array+i) = *((unsigned char *)m->array+startRow*m->dshape.shape[3]+i);
					break;
				case d_char:
					*((char *)subm->array+i) = *((char *)m->array+startRow*m->dshape.shape[3]+i);
					break;
				case d_int:
					*((int *)subm->array+i) = *((int *)m->array+startRow*m->dshape.shape[3]+i);
					break;
				case d_uint:
					*((unsigned int *)subm->array+i) = *((unsigned int *)m->array+startRow*m->dshape.shape[3]+i);
					break;
				case d_float:
					*((float *)subm->array+i) = *((float *)m->array+startRow*m->dshape.shape[3]+i);
					break;
				case d_double:
					*((double *)subm->array+i) = *((double *)m->array+startRow*m->dshape.shape[3]+i);
					break;
			}
		}
	}
	return subm;
}

Matrix *getSecondOrderMatrixColumes(Matrix *m,int startColume,int endColume){
	int i = 0,j,w,x,y,z;
	if(!m) return NULL;
	Matrix *subm = NULL;
	if(startColume >= 0 || startColume < m->dshape.shape[3] || endColume <= m->dshape.shape[3] || endColume > startColume){
		subm = (Matrix *)malloc(sizeof(Matrix));
		if(!subm) return NULL;
		subm->dtype = m->dtype;
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
		switch(m->dtype){
			case d_uchar:
				subm->array = (unsigned char *)malloc(subm->length*sizeof(unsigned char));
				break;
			case d_char:
				subm->array = (char *)malloc(subm->length*sizeof(char));
				break;
			case d_int:
				subm->array = (int *)malloc(subm->length*sizeof(int));
				break;
			case d_uint:
				subm->array = (unsigned int *)malloc(subm->length*sizeof(unsigned int));
				break;
			case d_float:
				subm->array = (float *)malloc(subm->length*sizeof(float));
				break;
			case d_double:
				subm->array = (double *)malloc(subm->length*sizeof(double));
				break;
		}
		if(!subm->array){
			free(subm);
			return NULL;
		}
		for(i=0;i<subm->length/z;i++){
			switch(subm->dtype){
				case d_uchar:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((unsigned char *)subm->array+i*z+j) = *((unsigned char *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
				case d_char:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((char *)subm->array+i*z+j) = *((char *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
				case d_int:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((int *)subm->array+i*z+j) = *((int *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
				case d_uint:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((unsigned int *)subm->array+i*z+j) = *((unsigned int *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
				case d_float:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((float *)subm->array+i*z+j) = *((float *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
				case d_double:
					for(j=0;j<subm->dshape.shape[3];j++){
						*((double *)subm->array+i*z+j) = *((double *)m->array+i*m->dshape.shape[3]+startColume+j);
					}
					break;
			}
		}
	}
	return subm;
}

Matrix *getSecondOrderSubMatrix(Matrix *m,int startRow,int startColume,int endRow,int endColume){
	Matrix *m1 = NULL,*m2 = NULL;
	m1 = getSecondOrderMatrixRows(m,startRow,endRow);
	m2 = getSecondOrderMatrixColumes(m1,startColume,endColume);
	destroyMatrix(m1);
	return m2;
}


