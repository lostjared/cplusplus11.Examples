#include<iostream>
#include<vector>
#include<string>
#include<utility>


class Type {
    
public:
    Type() = default;
    
    Type(const Type &type) : text(type.text), values(type.values) {}
    
    Type(Type&& type) : text(std::move(type.text)), values(std::move(type.values)) {}
    
    
    Type &operator=(const Type &type) {
        text = type.text;
        values = type.values;
        std::cout << "Used &\n";
        return *this;
    }
    
    Type& operator=(Type&& r) {
        text = std::move(r.text);
        values = std::move(r.values);
        std::cout << "Used &&\n";
        return *this;
    }
    
    void createValues() {
        for(unsigned int i = 0; i < 1000; ++i)
            values.push_back(i);
        
        text = "Value";
    }
    
    void printValues()  {
        for(auto i = values.begin(); i != values.end(); ++i) {
            std::cout << *i << ", ";
        }
    }
    
private:
    std::string text;
    std::vector<int> values;
    
};

template<typename T>
Type factoryCreate(T &&type) {
    type.createValues();
    return std::forward<T>(type);// std::move would cause RVO (Return value optimization) to not work
    // so conditional forward
}




int main(int argc, char **argv) {
    Type type_value, other_type;
    other_type.createValues();
    type_value = factoryCreate(other_type);
    type_value.printValues();
    
    return 0;
    
}