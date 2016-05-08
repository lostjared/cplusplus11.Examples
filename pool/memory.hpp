#ifndef __MEMORY_H__
#define __MEMORY_H__
#include<vector>
#include<cstdlib>
#include<iostream>

namespace pool {
    
    
    // prototype
    class Alloc {
    public:
        Alloc() = default;
        // cannot copy
        Alloc(Alloc &) = delete;
        void operator=(Alloc &) = delete;
        // allocation / deallocation
        void drain();
        void *alloc(unsigned int size);
        void *zero_alloc(unsigned int size);
        
        // Destructor
        ~Alloc();
    protected:
        std::vector<void *> memory;
    };
    
    // implementaion
    void Alloc::drain() {
        std::cout << "Draining pool of " << memory.size() << " releasing pointers..\n";
        if(memory.empty()) return;
        for(auto i = memory.begin(); i != memory.end(); ++i) {
            std::cout << "Releasing Pointer address: 0x" << std::hex << (unsigned long)*i << "\n";
            free(*i);
        }
        memory.erase(memory.begin(), memory.end());
    }
    
    void *Alloc::alloc(unsigned int size) {
        void *buffer = malloc(size);
        memory.push_back(buffer);
        return buffer;
    }
    
    void *Alloc::zero_alloc(unsigned int size) {
        void *buffer = calloc(1, size);
        memory.push_back(buffer);
        return buffer;
    }
    
    
    Alloc::~Alloc() {
        drain();
    }
}


#endif
