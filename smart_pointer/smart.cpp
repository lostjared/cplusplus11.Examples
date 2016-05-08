#include<iostream>
#include<memory>


// a simple user type to practice smart pointers
template<typename T>
class UserType {
public:
    UserType() { type = T(); }
    UserType(const T &t) : type(t) { }
    
    void print() {
        std::cout << type << " ";
    }
    
    void set(const T t) {
        type = t;
    }
    
protected:
    T type;
    
};


void test(std::shared_ptr<UserType<int>> passedValue) {
    passedValue->set(200);
    std::cout << "value is: ";
    passedValue->print();
}

void testPointer() {
    
    auto deleter = [](UserType<int> *type1) {
        std::cout << "Deleteing..\n";
        delete type1;
    };
    
    std::shared_ptr<UserType<int>> value1(new UserType<int>(100), deleter);
    for(unsigned int i = 0; i < 10; ++i) {
        std::cout << "{ ";
        value1->print();
        std::cout << "}\n";
    }
    test(value1); // add to reference count
    std::cout << "value1's value is now: ";
    value1->print();
    
}

int main(int argc, char **argv) {
    
    auto deleter = [](UserType<int> *type) {
        std::cout << "Deleting UserType for unique on destructor..\n";
        delete type;
    };
    
    
    std::unique_ptr<UserType<int>, decltype(deleter)> first(new UserType<int>(25), deleter);
    testPointer();
    std::cout << "Unique's value: ";
    first->print();
    std::cout << "\n";
    
    
    return 0;
}