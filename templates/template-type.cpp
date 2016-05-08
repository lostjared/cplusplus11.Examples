/* using template type for value */

#include<iostream>
#include<string>

template<typename T, T value>
class Temp {
public:
    Temp() : val(value) {}
    T val;
};

int main() {
    
// works
    Temp<int, 255> t;
    std::cout << t.val << "\n";

//    error
//    Temp<float, 4.5f> error_value;
    
    return 0;
}