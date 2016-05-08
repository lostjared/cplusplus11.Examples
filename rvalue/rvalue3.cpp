#include<iostream>
#include<vector>
#include<chrono>

class Container {
public:
    Container() = default;
    Container(std::initializer_list<int> values) : total(values) {}
    Container(const Container &c) {
        std::cout << "Used &\n";
        total = c.total;
    }
    
    // RValue Reference
    Container(Container &&c) {
        std::cout << "Used &&\n";
        total = std::move(c.total);
    }
    
    void add(std::initializer_list<int> values) {
        for(auto &i : values) {
            total.push_back(i);
        }
    }
    
    void printValues() {
        for(auto &i : total) std::cout << i << ", ";
        std::cout << "\n";
    }
    
protected:
    std::vector<int> total;
};


int main(int argc, char **argv) {
    using namespace std;
    
    std::cout << "Fill vector with values..\n";
    
    Container c = {0, 1, 2, 0, 4 , 25, 6};

    for(unsigned int i = 0; i < 25000; ++i)
        c.add({255, 255, 0, 255, 1024, 2048});
    
    
    auto n1 = chrono::high_resolution_clock::now();
    
    Container values(std::move(c));
    
    auto n2 = chrono::high_resolution_clock::now();
    
    std::cout << "Move operation took " << chrono::duration_cast<chrono::nanoseconds>(n2-n1).count() << " nanoseconds.\n";
    
    auto n3 = chrono::high_resolution_clock::now();
    
    Container copied_values(values);
    
    auto n4 = chrono::high_resolution_clock::now();
    
    std::cout << " Copy operation took: " << chrono::duration_cast<chrono::nanoseconds>(n4-n3).count() << " nanoseconds.\n";
    
    return 0;
}