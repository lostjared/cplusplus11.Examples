/*
 
 Simple template in C++11
 
 written by Jared Bruni
 http://lostsidedead.com
 
*/




#include<iostream>



template<typename T, int R, int C>
class Matrix {
    T buffer[R][C] = {};
public:
    Matrix();
    Matrix(const Matrix<T,R,C> &m);
    
    T &operator()(int r, int c) {
        return buffer[r][c];
    }
    
    bool operator==(const Matrix<T,R,C> &m);
    bool operator!=(const Matrix<T,R,C> &m);
    void fill(T t);
    friend std::ostream &operator<<(std::ostream &out, const Matrix<T,R,C> &m) {
        for(signed int i = 0;  i < R; ++i) {
            for(signed int z = 0; z < C; ++z) {
                out << m.buffer[i][z] << " ";
            }
            out << "\n";
        }
        return out;
    }
    
private:
    void assign(const Matrix<T,R,C> &m);
    
};

template<typename T, int R, int C>
Matrix<T,R,C>::Matrix()  {
    
}


template<typename T, int R, int C>
Matrix<T,R,C>::Matrix(const Matrix<T,R,C> &m) {
    assign(m);
}


template<typename T, int R, int C>
bool Matrix<T,R,C>::operator==(const Matrix<T,R,C> &m) {
    for(signed int i = 0; i < R; ++i) {
        for(signed int z = 0; z < C; ++z) {
            if(buffer[i][z] != m.buffer[i][z])
                return false;
            
        }
    }
    return true;
}

template<typename T, int R, int C>
bool Matrix<T,R,C>::operator!=(const Matrix<T,R,C> &m) {
    return (!this->operator==(m));
}

template<typename T, int R, int C>
void Matrix<T,R,C>::fill(T t) {
    for(signed int i = 0; i < R; ++i){
        for(signed int z = 0; z < C; ++z) {
            buffer[i][z] = t;
        }
    }
}

template<typename T, int R, int C>
void Matrix<T,R,C>::assign(const Matrix<T,R,C> &m) {
    for(signed int i = 0; i < R; ++i) {
        for(signed int z = 0; z < C; ++z) {
            buffer[i][z] = m.buffer[i][z];
        }
    }
}



int main (int argc, char **argv) {
 
    Matrix<char, 10, 10> m1, m2;

    m1(0, 0) = 'X';
    m2(0, 0) = 'O';
    
    if(m1 == m2) {
        std::cout << "Equal\n";
    } else {
        m1(0, 0) = 'O';
        if(m1 == m2) {
            std::cout << "Success!\n";
            m1.fill('Y');
            m2.fill('X');
            if(m1 != m2) {
                std::cout << "Works\n";
                std::cout << m1 << "\n" << m2 << "\n";
            }
            
        } else {
            std::cout << "failure\n";
        }
   }
    return 0;
}