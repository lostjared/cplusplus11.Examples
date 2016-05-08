#include<iostream>
#include<iomanip>
#include<string>

template /* template parameters */<typename T, int X, int Y>
class Matrix {
public:
    
    Matrix() {
        clear();
    }
    
    void clear() {
        for(unsigned int i = 0; i < X; ++i) {
            for(unsigned int z = 0; z < Y; ++z) {
                matrix[i][z] = T();
            }
        }
    }
    
    void add(Matrix<T,X,Y> &m) {
        for(unsigned int i = 0; i < X; ++i) {
            for(unsigned int z = 0; z < Y; ++z) {
                matrix[i][z] += m.matrix[i][z];
            }
        }
    }
    
    void sub(Matrix<T,X,Y> &m) {
        for(unsigned int i = 0; i < X; ++i) {
            for(unsigned int z = 0; z < Y; ++z) {
                matrix[i][z] -= m.matrix[i][z];
            }
        }
    }
    
    void mul(Matrix<T,X,Y> &m) {
        for(unsigned int i = 0; i < X; ++i) {
            for(unsigned int z = 0; z < Y; ++z) {
                matrix[i][z] *= m.matrix[i][z];
            }
        }
    }
    
    void div(Matrix<T,X,Y> &m) {
        for(unsigned int i = 0; i < X; ++i) {
            for(unsigned int z = 0; z < Y; ++z) {
                if(m.matrix[i][z] != 0)
                matrix[i][z] /= m.matrix[i][z];
            }
        }
    }
    
    T &operator()(int x, int y) { return matrix[x][y]; }
    
    void print() {
        std::cout << "Values = \n";
        for(unsigned int i = 0; i < X; ++i) {
            std::cout << "[ ";
            
            for(unsigned int z = 0; z < Y; ++z) {
                std::cout << std::setw(4) << matrix[i][z] << " ";
            }
            std::cout << " ]\n";
        }
    }
    
private:
    T matrix[X][Y];
};

// declarations:
/* 
 class C;
 extern int x;
*/
// definitions
/* 
 class C {];
 int x;
*/


int main() {
    
    Matrix /* template arguments */<float, 8, 8>  matrix1, matrix2;
    
    for(unsigned int i = 0; i < 8; ++i) {
        for(unsigned int z = 0; z < 8; ++z) {
            matrix1(i, z) = i*i*0.1f;
            matrix2(i, z) = z*z*0.1f;
        }
    }
    
    matrix1.add(matrix2);
    matrix1.print();
    matrix1.mul(matrix2);
    matrix1.print();
    
    return 0;
}