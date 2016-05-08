

#include<iostream>
#include<cassert>

// main function
int main() {
    int x = 1;
    int y = 5;
    std::cout << "(x+y) == 5\n";
    // assert should be true
    assert((x*y) == 5);
    char *ptr = new char [100];
    // should be true
    assert(ptr != 0);
    delete [] ptr;
    ptr = 0;
    // should fail
    assert(ptr != 0);
	return 0;
}
