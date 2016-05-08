/*
 written by Jared Bruni
 http://lostsidedead.com
 
 template stuff
 
*/



#include<iostream>

namespace mx {

    // a example type to use with generic average template function
    
    template<typename T, signed int Row>
    class Vec  {
        T members[Row] = {};
    public:
        Vec();
        Vec(Vec<T,Row> &v);
        void fill(T t);
        
        T &operator[](signed int pos) {
            return members[pos];
        }
    
        friend std::ostream &operator<<(std::ostream &out, Vec<T,Row> &v) {
            for(signed int i = 0; i < Row; ++i) {
                out << v.members[i] << " ";
            }
            return out;
        }
        
        bool operator==(const Vec<T,Row> &v) {
            for(signed int i = 0; i < Row; ++i) {
                if(members[i] != v[i])
                    return false;
            }
            return true;
        }
        
        Vec<T,Row> &operator=(const Vec<T,Row> &v) {
            assign(v);
            return *this;
        }
        
        Vec<T,Row> operator+(Vec<T,Row> &v) {
            Vec<T,Row> v2(*this);
            for(signed int i = 0; i < Row; ++i)
                v2.members[i] += v[i];
            return v2;
        }
        
        bool operator!=(const Vec<T,Row> &v) {
            return (!this->operator==(v));
        }
        
    protected:
        void assign(const Vec<T,Row> &v);
    };
    
    // definition
    template<typename T, signed int Row>
    Vec<T,Row>::Vec() {
        
    }
    
    template<typename T, signed int Row>
    Vec<T,Row>::Vec(Vec<T,Row> &v) {
        assign(v);
    }
    
    template<typename T, signed int Row>
    void Vec<T,Row>::assign(const Vec<T,Row> &v) {
        for(signed int i = 0; i < Row; ++i) {
            members[i] = v.members[i];
        }
    }
    
    template<typename T, signed int Row>
    void Vec<T,Row>::fill(T t) {
        for(signed int i = 0; i < Row; ++i) {
            members[i] = t;
        }
    }
    
    
    // generic average function template
    
    template<typename T, typename T2>
    T2 average(T t, T2 max) {
        T2 total{};
        for(T2 i{}; i < max; ++i) {
            total += t[i];
        }
        total /= max;
        return total;
    }
}


int main(int argc, char **argv) {
    using namespace mx;
    
    mx::Vec<float, 4> vec4,vec4_test,vec4_test2;
    vec4.fill(1.0f);
    vec4_test.fill(6.0f);
    vec4 = vec4+vec4_test;
    vec4_test2 = vec4+vec4_test;
    std::cout << vec4 << "\n";
    std::cout << vec4_test2 << "\n";
    vec4_test[0] = 21.0f;
    vec4_test[1] = 25.0f;
    vec4_test[2] = 50.0f;
    vec4_test[3] = 50.0f;
    float avg = average<mx::Vec<float, 4>, float>(vec4_test, 4);
    std::cout << "Average of vec4_test { " << vec4_test << "} is: " << avg << "\n";
    
    return 0;
}