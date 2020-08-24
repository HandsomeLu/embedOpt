#include <iostream>
#include <random>
#include <vector>
#include <time.h>
 
using namespace std;
 
vector<vector<double>> initMatrix(int m, int n);
 
vector<vector<double>> multiply(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b);
 
vector<vector<double>>
multiply_block(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b, int block_size);

double gettrace(vector<vector<double>> &matrix);

bool isEqual(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b);
 
int main() {
    //m * p, p * n, and k represent the size of block
    int m = 1000000, p = 1000000, n = 1000000, k = 1000;
    auto matrix_a = initMatrix(m, p), matrix_b = initMatrix(p, n);
    vector<vector<double>> matrix_c(m, vector<double>(n, 0));
    clock_t startTime1, endTime1, startTime2, endTime2;
    startTime1 = clock(); //计时开始
    auto matrix_c_1 = multiply_block(matrix_a, matrix_b, k);
    endTime1 = clock(); //计时结束
    cout<<"The run time1 is: "<<(double)((endTime1 - startTime1))<<" ms"<<endl;
    double trace1=gettrace(matrix_c_1);
    cout<<"trace1:"<<trace1<<endl;
    startTime2 = clock(); //计时开始
    auto matrix_c_2 = multiply(matrix_a, matrix_b);
    endTime2 = clock(); //计时结束
    cout<<"The run time is: "<<(double)((endTime2 - startTime2))<<" ms"<<endl;
    double trace2=gettrace(matrix_c_2);
    cout<<"trace2:"<<trace2<<endl;
    cout << isEqual(matrix_c_1, matrix_c_2);
    return 0;
}
 
vector<vector<double>> initMatrix(int m, int n) {
    vector<vector<double>> res(m, vector<double>(n, 0));
    default_random_engine engine;
    uniform_real_distribution<double> u(0.0, 200);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = u(engine);
        }
    }
    return res;
}
 
 
// normal matrix multiplication 
vector<vector<double>> multiply(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b) {
    int m = matrix_a.size(), p = matrix_a[0].size(), n = matrix_b[0].size();
    vector<vector<double>> res(m, vector<double>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                res[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    return res;
}

double gettrace(vector<vector<double>> &matrix){
    double trace;
    for(int i=0;i<matrix.size();i++){
        trace+=matrix[i][i];
    }
    return trace;
}
 
// block-based matrix multiplication
vector<vector<double>>
multiply_block(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b, int block_size) {
    int m = matrix_a.size(), p = matrix_a[0].size(), n = matrix_b[0].size();
    vector<vector<double>> res(m, vector<double>(n, 0));
    for (int bi = 0; bi < m; bi += block_size) {
        for (int bj = 0; bj < n; bj += block_size) {
            for (int bk = 0; bk < p; bk += block_size) {
                for (int i = bi; i < min(bi + block_size, m); ++i) {
                    for (int j = bj; j < min(bj + block_size, n); ++j) {
                        for (int k = bk; k < min(bk + block_size, p); ++k) {
                            res[i][j] += matrix_a[i][k] * matrix_b[k][j];
                        }
                    }
                }
            }
        }
    }
    return res;
}
 
// to check whether the two results are same
bool isEqual(vector<vector<double>> &matrix_a, vector<vector<double>> &matrix_b) {
    int m_a = matrix_a.size(), n_a = matrix_a[0].size();
    int m_b = matrix_b.size(), n_b = matrix_b[0].size();
    if (m_a != m_b || n_a != n_b)
        return false;
    for (int i = 0; i < m_a; ++i) {
        for (int j = 0; j < n_a; ++j) {
            if (matrix_a[i][j] != matrix_b[i][j])
                return false;
        }
    }
    return true;
}