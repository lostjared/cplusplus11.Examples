/* C++11 example
 istringstream example
 
 enter a variable name followed by 4 integers
 it will add together the integers
*/

#include<iostream>
#include<string>
#include<sstream>

typedef struct _Values {
    std::string name;
    int x,y,w,h;
} Values;


bool convertText(std::string text, Values &v) {
    std::istringstream stream(text);
    stream >> v.name >> v.x >> v.y >> v.w >> v.h;
    if(stream.fail()) return false;
    return true;
}

int main(int argc, char **argv) {
    std::string text;
    std::getline(std::cin, text);
    Values v;
    if(convertText(text, v) == true) {
        std::cout << v.name << " values = [" << v.x << "," << v.y << "," << v.w << "," << v.h << "]; \n";
        
        int total=v.x+v.y+v.w+v.h;
        std::cout << "The total is "  << total << "\n";
    }
    else {
        std::cerr << "Failed to convert \n";
    }
    return 0;
}

