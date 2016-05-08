#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

template<typename T>
class ForEach_Function {
public:
    // pass in needed variables here
    ForEach_Function(std::string t) : text(t) {
        
    }
    // overload () operator
    void operator()(const T& type) {
        std::cout << text << " " << type << "\n";
    }
    
private:
    std::string text;
};


int main() {
    std::vector<std::string> vec1 {"jared", "bruni", "LostSideDead"};
    // initalize function object
    ForEach_Function<std::string> fobject("Vector of type string");
    // use function object
    std::for_each(vec1.begin(), vec1.end(), fobject);
    
    std::vector<int> vec2{0, 1999, 2015, 360};
    // initalize function object
    ForEach_Function<int> fiobject("Vector of type int");
    // use function object
    std::for_each(vec2.begin(), vec2.end(), fiobject);
    return 0;
}