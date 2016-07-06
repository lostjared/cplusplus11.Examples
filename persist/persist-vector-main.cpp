#include"persist-vector.hpp"
#include<sstream>
struct Record {
    char str_value[100];
    int data;
    
};

class CustomRead {
public:
    void operator()(std::string &type, std::fstream &file) {
        unsigned int value = 0;
        file.read(reinterpret_cast<char*>(&value), sizeof(unsigned int));
        char *tmp = new char[value+1];
        file.read(tmp, value);
        type = tmp;
        delete [] tmp;
    }
};

class CustomWrite {
public:
    void operator()(std::string &type, std::fstream &file) {
        unsigned int value = type.length();
        file.write(reinterpret_cast<char*>(&value), sizeof(value));
        file.write(type.c_str(), value);
    }
};

void outputItems(persist::Vector<Record> &pv) {
    for(auto start = pv->begin(), stop = pv->end(); start != stop; ++start) {
        std::cout << "Record string: " << start->str_value << "\n";
        std::cout << "Record integer: " << start->data << "\n\n\n";
    }
}
void outputCustomItems(persist::Vector<std::string, CustomRead, CustomWrite> &cv) {
    for(unsigned int i = 0; i < cv->size(); ++i) {
        std::cout << "Value: " << cv[i] << "\n";
    }
}


int main(int argc, char **argv) {
    persist::Vector<Record> pv("file.txt", 100);
    outputItems(pv);
    persist::Vector<std::string, CustomRead, CustomWrite> cv("custom.txt", 100);
    outputCustomItems(cv);
    
    std::ostringstream stream;
    stream << "test run @ " << static_cast<unsigned int>(time(0)) << "\n";
    cv->push_back(stream.str());
    
    Record r;
    std::cout << "Enter string: ";
    std::cin >> r.str_value;
    std::cout << "Enter integer: ";
	std::cin >> r.data;
	pv->push_back(r);
    
    return 0;
}