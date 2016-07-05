#include"persist-vector.hpp"

struct Record {
    char str_value[100];
    int data;
    
};

void outputItems(persist::Vector<Record> &pv) {
    for(auto start = pv->begin(), stop = pv->end(); start != stop; ++start) {
        std::cout << "Record string: " << start->str_value << "\n";
        std::cout << "Record integer: " << start->data << "\n\n\n";
    }
}


int main(int argc, char **argv) {
    persist::Vector<Record> pv("file.txt", 100);
    outputItems(pv);
    for(unsigned int i = 0; i < 4; ++i) {
        Record r;
        std::cout << "Enter string: ";
        std::cin >> r.str_value;
        std::cout << "Enter integer: ";
        std::cin >> r.data;
        pv->push_back(r);
    }
    return 0;
}