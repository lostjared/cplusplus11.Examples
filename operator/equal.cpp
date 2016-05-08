#include<iostream>

template<typename T>
class Complex {
public:
    Complex() : t1{}, t2{} { }
    Complex(T tt1, T tt2) : t1{tt1}, t2{tt2} { }
    Complex(const Complex<T> &c) : t1{c.t1}, t2{c.t2} {
    }
    Complex &operator=(const Complex<T> &c) {
        t1 = c.t1;
        t2 = c.t2;
        return *this;
    }
    
    Complex operator+(const Complex<T> &c) {
        Complex<T> t(*this);
        t.t1 += c.t1;
        t.t2 += c.t2;
        return t;
    }
    
    T one() const { return t1; }
    T two() const { return t2; }

private:
    T t1, t2;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Complex<T> &c) {
    out << "<" << c.one() << ":" << c.two() << ">";
    return out;
}

int main() {
    
    Complex<float> f(100.0f, 100.0f), f2(100.0f, 104.0f);
    
    f = f + f2;
    std::cout << f << "\n";
    
    return 0;
}