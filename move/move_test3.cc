/*

 written by Jared Bruni
 http://lostsidedead.com
 
*/

#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<chrono>

class Value {
public:
    Value();
    Value(Value &&v);
    Value(const Value &v);
    void setKey(std::string one, std::string two);
    std::string getKey(std::string one);
    std::unordered_map<std::string, std::string> values;
};

Value::Value() { }

Value::Value(Value &&v) : values{std::move(v.values)} {
    
}

Value::Value(const Value &v) : values{v.values} {
    
}

void Value::setKey(std::string one, std::string two) {
    values[one] = two;
}

std::string Value::getKey(std::string one) {
    return values[one];
}

int main(int argc, char **argv) {
    std::cout << "Filling map.\n";
    Value values;
    for(int i = 0; i < 25000; ++i) {
        std::ostringstream stream;
        stream << "Value number: " << i;
        std::ostringstream stream2;
        stream2 << i;
        values.setKey(stream2.str(), stream.str());
    }
    std::cout << "Here it is: \n";
    for(auto &i : values.values) {
        std::cout << i.first << ": " << i.second << "\n";
    }
    std::cout << "Move value: ";
    auto start = std::chrono::high_resolution_clock::now();
    Value moveValue(std::move(values));
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "move operation took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count() << " nanoseconds\n";
    
    auto start2 = std::chrono::high_resolution_clock::now();
    Value copiedValue(moveValue);
    auto stop2 = std::chrono::high_resolution_clock::now();
    
    std::cout << "copy operation took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop2-start2).count() << " nanoseconds\n";
    
    return 0;
}

