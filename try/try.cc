/* This seems odd to me but it works, instead of a regular block
  we can use a try block instead */

#include<iostream>


void function(int x)
try {
    std::cout << x << " is the value\n";
    throw 1;
}
catch(...) {
    std::cerr << "Error \n";
}


class Value {
public:
    Value() = default;
    
    void pass(int x)
    try {
        function(x);
        function(20);
    } catch(...) {
        
    }
};

int main()
try {
    std::cout << "Example Try blocks\nEnter something:\n";
    Value v;
    int x;
    std::cin >> x;
    v.pass(x);
    return 0;
}
catch(std::exception &e) {
    
    return -1;
}
catch(...) {
    
    return -1;
}


