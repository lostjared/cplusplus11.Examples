#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

struct Point { int x, y; };

void PrintPoint(struct Point *p) {
    std::cout << p->x << ":" << p->y << "\n";
}

int main(int argc, char **argv) {
    
    struct Point *p;
    
    p = (Point*)malloc(sizeof(Point)); // allocate on the heap
    memset(p, 0, sizeof(Point));
    
    p->x = 100;
    p->y = 200;
    
    PrintPoint(p);
    
    free(p); // free
    
    p = (Point*)calloc(1, sizeof(Point)); // allocate / initalize to zero
    
    PrintPoint(p);
    
    free(p); // free
    
    return 0;
}
