/* Variadic template 
 written by Jared Bruni
 http://lostsidedead.com
 */


#include<iostream>
#include<string>


class Point { public: int x, y; };
class Rect  { public: Point p1, p2; };
class Text { public: Point pos; std::string text; };


std::ostream &operator<<(std::ostream &out, Point &p) {
    out << p.x << ", " << p.y << " ";
    return out;
}

// variable number of bases

template<typename ...BaseTypes>
class Test : public BaseTypes... {
public:
    Test(const BaseTypes&... b) : BaseTypes(b)... {}
    size_t sizeTypes() { return sizeof...(BaseTypes); }
    
};

int main(int argc, char **argv) {
    try {
        Test<Point> test1({0,0});
        Test<Point,Rect> test2({0,0}, {{0,0},{640,480}});
        Test<Point,Rect,Text> test3({0,0}, {{0,0},{480,272}}, {{25,25}, {"Hello world Test"}});
        
        std::cout << "sizeof... " << test3.sizeTypes() << " Text: " << test3.text << "\n";
        std::cout << "Points: " << test3.p1 << test3.p2 << "\n";
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}