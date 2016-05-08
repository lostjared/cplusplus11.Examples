/*

 How to create a  Pointer to member function of a class
 -Jared Bruni

*/


#include<iostream>
#include<string>


class Point {
public:
    Point() = default;
    Point(const int &xx, const int &yy) : x(xx), y(yy) {
        
    }
    void setXY(const int &xx, const int &yy) {
        x = xx;
        y = yy;
    }
    int getX() const { return x; }
    int getY() const { return y; }
    
    int addTogether() { return x+y; }
    int mulTogether() { return x*y; }
    
protected:
    int x,y;
    
    
};

int main() {
    // pointer to member function
    int (Point::*mem_ptr)() = &Point::addTogether;
    
    Point p(100,100);

    // use pointer to class/member function
    int value = (p.*mem_ptr)();
    
    std::cout << "Value:" << value << "\n";

    mem_ptr = &Point::mulTogether;
    
    value = (p.*mem_ptr)();
    
    std::cout << "Value: " << value << "\n";
    
    return 0;
}