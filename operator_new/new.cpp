/* overloaded opreator new */

#include<iostream>
#include<vector>
#include<string>

int call_new = 0;

void *operator new(std::size_t size) {
    std::cout << "Allocated: " << size << " at " << "test" << "\n";
    ++call_new;
    return std::malloc(size);
}

void operator delete(void *p) noexcept {
    std::cout << "Deleted\n";
    std::free(p);
    --call_new;
}

void checkIfEqual() {
    if(call_new == 0) {
        std::cout << "All new matched with delete..\n";
    } else {
        std::cout << "New not matched with delete " << call_new << " Times...\n";
    }
}
    
int main(int argc, char **argv) {
   

    int *x = new int;
    delete x;
    
     std::string *s = new std::string();
    
    checkIfEqual();

    int *values[8];
    for(unsigned int v = 0; v < 8; ++v) values[v] = new int;
    
    for(unsigned int v = 0; v < 8; ++v) delete values[v];
    
    checkIfEqual();
    return 0;
}