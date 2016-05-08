//
//  Member
//
//  Created by Jared Bruni on 7/9/13.


#include <iostream>

enum class Direction { left, right };

class MemberDecl {
public:
    int var = 0, type = 1; // you can now init here for members
    char c = 'C';
    MemberDecl() = default;
    Direction dir = Direction::left;
    
    void Func() {
        std::cout << var << " : " << type << " " << c << "\n";
    }
};


int main(int argc, char **argv) {
    MemberDecl m;
    m.Func();
    return 0;
}