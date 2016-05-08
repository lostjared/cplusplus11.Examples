

#include<iostream>
#include<vector>
#include<string>


template<typename T>
class ArrayOf {
public:
    void add(std::initializer_list<T> add) {
        for(auto &i : add)
            v.push_back(i);
    }
    
    void printOut() {
        for(auto &i : v) {
            std::cout << i << "\n";
        }
    }

private:
    std::vector<T> v;
    
};


int main() {

    ArrayOf<std::string> init;
    init.add({"One", "Two", "Three", "Four" });
    init.printOut();
    return 0;
}