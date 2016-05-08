/*
 C++11 Example using std::allocator
 written by Jared Bruni
*/


#include<iostream>


template<typename Type,typename Allocator = std::allocator<Type>>
class Allocated_Array {

public:
    typedef typename Allocator::size_type size_type;
    size_type set_size;
    
    Allocated_Array() : set_size{}, type(nullptr), last(nullptr) {
        
    }
    
    Allocated_Array(size_type length): set_size{}, type(nullptr),last(nullptr) {
        if(length != 0)
        sizeTo(length);
    }
    
    ~Allocated_Array() {
        clean();
    }
    
    void clean() noexcept {
        if(type != nullptr) {
            allocator.deallocate(type,last-type);
            type = nullptr;
        }
    }
   
    Type *getType() const {
        return type;
    }
    
    Type &operator[](unsigned int pos) {
        return type[pos];
    }
    
    size_type size() const {
        return set_size;
    }
    
    void erase_and_resize(size_type s) {
        sizeTo(s);
    }
    
private:
    Allocator allocator;
    Type *type;
    Type *last;
    
    void sizeTo(size_type length) {
        if(type != nullptr) clean();
        type = allocator.allocate(length);
        set_size = length;
        last = type+set_size;
    }
};

// entry point
int main(int argc, char **argv) {
    try {
        Allocated_Array<int> arrSize(10);
        unsigned int array_size = arrSize.size();
        for(unsigned int i = 0; i < array_size; ++i) {
            arrSize[i] = rand()%255;
            std::cout << arrSize[i] << "\n";
        }
        std::cout << "Enter size of array: ";
        unsigned int value = 0;
        std::cin >> value;
        if(value == 0) return 0;
        Allocated_Array<char> arrSize2(value);
        //arrSize2.erase_and_resize(value);
        std::cout << "random array of size: " << value << "\n";
        array_size = arrSize2.size();
        for(unsigned int z = 0; z < array_size; ++z) {
            arrSize2[z] = 'a'+rand()%23;
            std::cout << z << ": " << arrSize2[z] << "\n";
        }
        std::cout << "\n";
    }
    catch(...) {
        std::cerr << "Exception thrown..\n";
    }
    return 0;
}

