/* C++11 C++ style cast tests
 written by Jared Bruni
 http://objective-c.info
 
*/


#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<exception>
#include<typeinfo>


class Modify {
public:
    virtual ~Modify() { }
    Modify(char *temp) {
        strncpy(temp, "value", 5);
        this->temp = temp;
    }
    void output() {
        std::cout << temp << "\n";
    }
protected:
    char *temp;
};

class ModifyPrint : public Modify {
public:
    virtual ~ModifyPrint() { }
    ModifyPrint() = default;
    ModifyPrint(char *temp) : Modify(temp) { }
    void output() {
        std::cout << "Value is: " << temp << "\n";
    }
    
};


struct Values {
    int x,y,z;
    unsigned long value;
    Values() = default;
    Values(int x, int y, int z, unsigned long value) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->value = value;
    }
};

void castTest(Modify &m) {
    try {
        ModifyPrint &p = dynamic_cast<ModifyPrint&>(m);
        p.output();
        std::cout << "Cast succeded.\n";
    } catch(std::bad_cast &e) {
        std::cout << "Cast test:\n";
        std::cerr <<  "Exception: " << e.what() << "\n";
        std::cerr << "Cast is not of type ModifyPrint..\n";
    }
}

int main(int argc, char **argv) {
    
    const char *text = new char [6];

    // remove const
    Modify m(const_cast<char*>(text));
    m.output();
    
    
    std::fstream file;
    file.open("text.txt", std::ios::out | std::ios::binary);
    if(!file.is_open()) {
        std::cerr << " Could not open text.txt\n";
        return -1;
    }
    
    Values val(100, 100, 200, 200);
    // reinterpret_cast from one type to another
    file.write(reinterpret_cast<char*>(&val), sizeof(val));
    file.close();
    
    // cast from long to int
    int x = 0;
    long value = 0xFFFF;
    x = static_cast<int>(value);
    
    std::cout << "Here is the value: " << x << " ..\n";
 
    Modify *values[3];
    values[0] = new ModifyPrint(const_cast<char*>(text));
    values[1] = new ModifyPrint(const_cast<char*>(text));
    values[2] = new Modify(const_cast<char*>(text));
    
    for(unsigned int i = 0; i < 3; ++i) {
        castTest(*values[i]);
        delete values[i];
    }
    
    delete [] text;
    
    
    return 0;
}
