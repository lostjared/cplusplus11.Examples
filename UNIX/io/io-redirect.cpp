#include<iostream>
#include<cstdio>
#include<cstdlib>

int main(int argc, char **argv) {
    
    
    if(argc != 3) {
        std::cerr << "Error program requires two arguments.\n" << argv[0] << " stdout stderr\n";
        return 0;
    }
    
    freopen(argv[1], "w", stdout);
    freopen(argv[2], "w", stderr);
    system("cat ./io-redirect.cpp");
    fclose(stdout);
    fclose(stderr);
    
    
    return 0;
}
