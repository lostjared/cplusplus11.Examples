/* 
 mutable example written by Jared Bruni
 purpose is to show how mutable can be used.
 
*/

#include<iostream>
#include<string>
#include<vector>

class StringOutput {
public:
    StringOutput(std::string n) : name{n} /* better */ {
        // name = n; // would init {} then =
        ++count;
    }
    mutable std::string name; // can change even when StringOutput type is const
    
private:
    static unsigned int count;
};

unsigned int StringOutput::count = 0;


std::ostream &operator<<(std::ostream &out, const StringOutput &sout) {
    if(sout.name.find("\n") == -1)
    sout.name += "\n"; //mutable so okay
    
    out << sout.name;
    return out;
}

int main(int argc, char **argv) {
    std::vector<StringOutput> vec_str;
    try {
        std::string value;
        while(value != "quit") {
            std::cout << "Enter value: ";
            std::cin >> value;
            vec_str.push_back(StringOutput(value));
            std::cout << vec_str.size() << " : " << vec_str[vec_str.size()-1];
        }
        for(auto &i : vec_str) {
            std::cout << i << " is the var\n";
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        
    }
    return 0;
}