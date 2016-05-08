/*

 override 
 http://lostsidedead.com
 
 shows how to use C++11 override and final
 written to help me remember.
 

*/


#include<iostream>
#include<string>

namespace mx {
    
    
    // some type to use
    template<typename T>
    class Point {
    public:
        Point(T x, T y) : xval{x}, yval{y} { }
        Point() : xval{0}, yval{0} { }
        
        Point(const Point &p) {
            setPoint(p);
        }
        
        Point(Point &p) {
            setPoint(p);
        }
        
        T getX() { return xval; }
        T getY() { return yval; }
        
    private:
        T xval, yval;
        void setPoint(Point &p) {
            xval = p.xval;
            yval = p.yval;
        }
        
    };
    
    
    template<typename T>
    std::ostream &operator<<(std::ostream &out, Point<T> &p) {
        out << "Point: " << p.getX() << " : " << p.getY() << " ";
        return out;
    }
    
    template<typename T>
    std::istream &operator>>(std::istream &in, Point<T> &p) {
        T x,y;
        in >> x >> y;
        p = Point<T>(x,y);
        return in;
    }
    
    class App {
    public:
        App(std::string n) : name{n} { }
        virtual ~App() { }
        virtual void run() = 0;// pure virtual
        virtual void init() { std::cout << "App init!\n"; }
        std::string getName() const{ return name; }
    private:
        std::string name;
    };

    class Demo : public App {
    public:
        Demo(std::string n) : App{n} {
            App::init();
        }
        // overrides virtual
        void run() override {
            std::cout << getName() << " Program started\n";
        }

        void init() override {
            std::cout << "Initialized " << getName() << "\n";
        }
    };
    
    class ThisProgram : public Demo {
    public:
        
        ThisProgram(std::string n) : Demo{n} {
            Demo::init();
        }
    
        void run() final { // final version
            // do some stuff
            std::cout << getName() << " program started.\n";
            // do whatever here.
            std::cout << "Enter two numbers: ";
            Point<signed int> input_point;
            std::cin >> input_point;
            std::cout << "Entered " << input_point << "\n";
        }
    };
    
    class SubProgram : public ThisProgram {
    public:
        SubProgram(std::string n) : ThisProgram{n} {
            init();
        }
        
        void init() override {
            std::cout << "Different Init.\n";
        }
    };
}

int main(int argc, char **argv) {
    
    try {
        mx::ThisProgram prog(argv[0]);
        prog.run();
        mx::SubProgram  subprog(argv[0]);
        subprog.run();
        
    } catch( ... ) {
        std::cerr << "Error .\n";
    }
    
    return 0;
    
}