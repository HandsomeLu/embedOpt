#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>
#include <time.h>
 
using namespace std;

float rand_float(float s);

double** initMatrix(int m, int n, float seed);

void multiply(double** &matrix_a, double** &matrix_b, double** &matrix_c, int n);

double gettrace(double** &matrix, int n);
 
int main() {
    //m * p, p * n, and k represent the size of block
    int m = 10000, p = 10000, n = 10000, k = 100;
    auto matrix_a = initMatrix(m, p,0.3), matrix_b = initMatrix(p, n,0.3);
    // 初始化结果矩阵
    double** matrix_c=new double*[m];
    for(int i=0;i<m;++i)  
        matrix_c[i]=new double[n]();  
    clock_t startTime1, endTime1, startTime2, endTime2;
    // startTime1 = clock(); //计时开始
    // auto matrix_c_1 = multiply_block(matrix_a, matrix_b, k);
    // endTime1 = clock(); //计时结束
    // cout<<"The run time1 is: "<<(double)((endTime1 - startTime1))<<" ms"<<endl;
    // double trace1=gettrace(matrix_c_1);
    // cout<<"trace1:"<<trace1<<endl;
    startTime2 = clock(); //计时开始
    multiply(matrix_a, matrix_b,matrix_c, n);
    endTime2 = clock(); //计时结束
    cout<<"The run time is: "<<(double)((endTime2 - startTime2))<<" ms"<<endl;
    double trace2=gettrace(matrix_c,n);
    cout<<"trace2:"<<trace2<<endl;
    // cout << isEqual(matrix_c_1, matrix_c_2);
    return 0;
}

float rand_float(float s){
	return 4*s*(1-s);
}

 
double** initMatrix(int m, int n, float seed) {
    double** res=new double*[m];
    for(int i=0;i<m;++i) {
        res[i]=new double[n];
    } 
    float s=seed;
	for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            s=rand_float(s);
		    res[i][j]=s;
        }
	}
    return res;
}
 
 
// normal matrix multiplication 
void multiply(double** &matrix_a, double** &matrix_b, double** &matrix_c, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    // return matrix_c;
}

double gettrace(double** &matrix, int n){
    double trace;
    for(int i=0;i<n;i++){
        trace+=matrix[i][i];
    }
    return trace;
}
 
// block-based matrix multiplication
void multiply_block(double** &matrix_a, double** &matrix_b, double** &matrix_c, int block_size, int n) {
    for (int bi = 0; bi < n; bi += block_size) {
        for (int bj = 0; bj < n; bj += block_size) {
            for (int bk = 0; bk < n; bk += block_size) {
                for (int i = bi; i < min(bi + block_size, n); ++i) {
                    for (int j = bj; j < min(bj + block_size, n); ++j) {
                        for (int k = bk; k < min(bk + block_size, n); ++k) {
                            matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                        }
                    }
                }
            }
        }
    }
}
 
// to check whether the two results are same
// bool isEqual(double** &matrix_a, double** &matrix_b) {
//     int m_a = matrix_a.size(), n_a = matrix_a[0].size();
//     int m_b = matrix_b.size(), n_b = matrix_b[0].size();
//     if (m_a != m_b || n_a != n_b)
//         return false;
//     for (int i = 0; i < m_a; ++i) {
//         for (int j = 0; j < n_a; ++j) {
//             if (matrix_a[i][j] != matrix_b[i][j])
//                 return false;
//         }
//     }
//     return true;
// }