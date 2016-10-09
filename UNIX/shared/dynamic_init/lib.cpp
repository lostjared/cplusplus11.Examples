#include<iostream>
#include "header.h"


void __attribute__((constructor)) init() {
    std::cout << "Init called..\n";
}

void __attribute__((destructor)) release() {
    std::cout << "Release called...\n";
}

void sayHello() {
    std::cout << "Hello World\n";
}
