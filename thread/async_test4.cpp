/* async test 
   written by Jared Bruni
   http://lostsidedead.com
 
*/


#include<iostream>
#include<future>
#include<thread>


int getIntegerValue() {
    int x;
    std::cout << "Enter integer value: ";
    std::cin >> x;
    return x;
}

int main(int argc, char **argv) {
    

    std::future<int> f = std::async(getIntegerValue);
    int value = f.get();
    std::cout << "Value Entered is: " << value << "\n";
    f = std::async(getIntegerValue);
    std::cout << "Value is: " << f.get() << "\n";
    
    return 0;
}