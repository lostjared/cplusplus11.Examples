#include<iostream>
#include<thread>
#include<future>
#include<string>
#include<exception>
#include<stdexcept>

void procData(std::promise<std::string> &p) {
    try {
        char character;
        std::cout << "Input character e to throw exception: ";
        std::cin >> character;
        if(character == 'e') {
            throw std::runtime_error("Exception character inputed\n");
        }
        std::string strValue = std::string("character: ") + character + " inputed";
        p.set_value(std::move(strValue));
    }
    catch (...) {
        p.set_exception(std::current_exception());
    }
}

int main(int argc, char **argv) {
    try {
        std::promise<std::string> promise_value;
        std::thread thread1(procData, std::ref(promise_value));
        thread1.detach();
        std::future<std::string> future_value(promise_value.get_future());
        std::cout << "Value returned: " << future_value.get() << "\n";
    }
    catch(const std::exception &e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Unknown Exception: \n";
    }
    return 0;
}