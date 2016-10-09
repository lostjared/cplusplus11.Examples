#include<iostream>
#include<string>
#include<dlfcn.h>

void error(const std::string &text);

typedef void (*sayHello)();

int main() {
    void *libHandle;
    
#if defined(__APPLE__)
    libHandle = dlopen("libdemo.dylib", RTLD_LAZY);
#else
    libHandle = dlopen("./libdemo.so", RTLD_LAZY);
#endif
    
    if(libHandle == NULL)
        error(dlerror());
    
    (void)dlerror();
    
    sayHello say;
    say = reinterpret_cast<sayHello>(dlsym(libHandle,"sayHello"));
    const char *e = dlerror();
    if(e != NULL)
        error(e);
    std::cout << "Shared Object: ";
    if(say != NULL)
        say();
    
    dlclose(libHandle);
    return EXIT_SUCCESS;
}


void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
