/* move test
  written by Jared Bruni
 
 http://lostsidedead.com
 
*/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>


class MoveVector {
public:
    explicit MoveVector(std::vector<std::string> &&v) : vec{v} {
        std::cout << "Moved vector\n";
    }
    void print() {
        for(auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
        
private:
    std::vector<std::string> vec;
    
};

int main(int argc, char **argv) {
    
    std::vector<std::string> vz;
    std::cout << "Filling vector..\n";
    for(unsigned int i = 0; i < 10000; ++i) {
        std::ostringstream stream;
        stream << i;
        vz.push_back(stream.str());
    }
    // instead of copying use move
    MoveVector v(std::move(vz));
    v.print();
    
    return 0;
}