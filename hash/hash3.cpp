/*
 
 C++11 hash table (unordered_map) test
 written by Jared Bruni
 http://objective-c.info
 
*/



#include<iostream>
#include<string>
#include<unordered_map>
#include<cstdlib>

class Variable {
public:
    Variable() : vname{}, vval{0} { }
    Variable(std::string name) : vname{name}, vval{0} { }
    Variable(std::string name, float value) : vname{name}, vval{value} {
        
    }
    std::string &name()  {
        return vname;
    }
    float &value() { return vval; }
    
protected:
    std::string vname;
    float vval;
    
};

std::ostream &operator<<(std::ostream &out, Variable &v) {
    out << v.name() << " = " << v.value() << "\n";
    return out;
}

int main(int argc, char **argv) {
    
    std::unordered_map<std::string, Variable> hashtable;
    
    for(;;) {
        std::cout << "Enter Number:\n1 add variable\n2 print out variable\n3 average variables\n4 quit.\n";
        std::string input, name, value;
        std::cin >> input;
        switch(atoi(input.c_str())) {
        case 1: {
                std::cout << "Enter variable name: ";
                std::cin >> name;
                std::cout << "Enter floating point value: ";
                std::cin >> value;
                hashtable[name].value() = atof(value.c_str());
                hashtable[name].name() = name;
        }
            break;
        case 2: {
                
            std::cout << "Enter variable name: ";
            std::cin >> name;
            std::cout << "value is: " << hashtable[name] << "\n";
        }
            break;
        case 3: {
            
            float average = 0;
            for(auto i = hashtable.begin(); i != hashtable.end(); ++i) {
                average += i->second.value();
            }
            
            average /= hashtable.size();
            std::cout << "Average is: " << average << "\n";
            
        }
            break;
        case 4:
                return 0;
            
        }
    }

    return 0;
}