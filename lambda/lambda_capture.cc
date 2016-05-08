/* Lambda expression capture test */

#include<iostream>
#include<string>
#include<vector>

class C {
    std::vector<std::string> &vec;
    std::string filename;
    signed int row_w, row_h;
public:
    C(std::string f, std::vector<std::string> &v) : vec(v),filename{f}, row_w{24}, row_h{0} {
    }
    void procFunction() {
        std::for_each(vec.begin(), vec.end(), [](std::string s) {
            std::cout << s << "\n";
        });
        signed int len = row_w;
        // some example lambda expressions
        auto test_1 = [len](int &ry) {
            ry += len;
        };
        auto test_2 = [=](int &ry) {
            ry *= len; // uses row_h from C
        };
        auto test_3 = [&](int &ry) {
            ry += row_w; // uses row_w from C
        };
        test_1(row_h);
        test_2(row_w);
        test_3(row_h);
        output();
    }
    
    void output() {
        std::cout << filename << " some test of lambda expression" << "row_w: " << row_w << " : row_h " << row_h << "\n";
    }
    
};

int main(int argc, char **argv) {
    std::vector<std::string> v = { "test", "test two" };
    C c("test", v);
    c.procFunction();
    return 0;
    
}