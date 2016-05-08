/* written by Jared Bruni
    http:// lostsidedead.com
*/


#include<iostream>
#include<type_traits>


template<typename T>
class Con {
public:
    // constexpr constructor is called a literal type. To be simple enough to be
    // constexpr a constructor must have a empty body.
    // Section 10.4.3 C++ Programming Language 4th Edition
    constexpr Con() {}
    
    constexpr static T square(const T val) { return val*val; }

    static_assert(sizeof(T)<=4, "Larger than 4 bytes.\n");
    static_assert(std::is_arithmetic<T>::value,"Is not numeric");
};

constexpr int v1 = 10;
constexpr int v2 = 20;

constexpr Con<int>  v;
constexpr int value=v.square(v1*v2);
int arr[value];


int main(int argc, char **argv) {
    // below would not pass static_assert
    // Con<std::string> v2;
    std::cout << " Size of array is: " << value << "\n";
    return 0;
}
