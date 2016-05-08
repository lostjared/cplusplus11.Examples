#include<iostream>
#include<vector>


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
    
    
    Container c = {0, 1, 2, 0, 4 , 25, 6};
    
    c.add({255, 255, 0, 255, 1024, 2048});
    
    Container values(std::move(c));
    
    values.printValues();
    

    values.add( {2098, 2, 4, 1 ,2,4} );
    
    Container copied_values(values);
    
    copied_values.printValues();
    
    return 0;
}