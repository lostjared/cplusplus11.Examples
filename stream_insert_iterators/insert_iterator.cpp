
// Insert Iterators demo
// Will insert with back_inserter or front_inserter


#include<iostream>
#include<algorithm>
#include<iterator>
#include<list>
#include<vector>
#include<set>
#include<deque>


template<typename T>
void Print(std::string data_type, std::ostream &out, T type) {
    out << "Inserted into " << data_type << " = { ";
    for(auto &i : type) {
        out << i << " ";
        
    }
    out << "}\n";
}

int main() {
    std::list<int> value1 = { 0,10,30,40,50 };
    std::vector<int> value2;
    std::copy(value1.begin(), value1.end(), std::back_inserter(value2));
    std::set<int> value3;
    std::copy(value1.begin(), value1.end(), std::inserter(value3, value3.begin()));
    std::deque<int> value4;
    std::copy(value1.begin(), value1.end(), std::front_inserter(value4));
    Print("Vector",std::cout, value2);
    Print("Set",std::cout, value3);
    Print("Deque",std::cout, value4);
    return 0;
}