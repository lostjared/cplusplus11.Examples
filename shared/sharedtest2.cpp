#include<iostream>
#include<memory>
#include<cstring>
#include<cctype>


// dummy class used to demonstrate std::shared_ptr
class StringPtr {
public:
    StringPtr(const char *szTemp) {
        temp = new char [ strlen(szTemp) + 1 ];
        strncpy(temp, szTemp, strlen(szTemp));
    }
    
    ~StringPtr() {
        if(temp) {
            std::cout << "Releasing: " << temp << "\n";
            delete [] temp;
        }
    }
    
    char &at(unsigned int i) { return temp[i]; }
    const char *str() { return temp; }
    unsigned int len() { return strlen(temp); }
    
private:
    char *temp;
};

// shared_ptr with StringPtr
std::shared_ptr<StringPtr> value;

// pass by reference
void procText(std::shared_ptr<StringPtr> &v) {
    for(unsigned int i = 0; i < v->len(); ++i) {
        v->at(i) = tolower(v->at(i));
    }
}
// pass by value
void printReversed(std::shared_ptr<StringPtr> v) {
    std::cout << "Value reversed: ";
    for(int i = v->len() - 1; i >= 0; --i) {
        std::cout << v->at(i);
    }
    std::cout << "\n";
}

// dummy main
int main(int argc, char **argv) {
    std::cout << "Enter value: ";
    std::string s;
    std::getline(std::cin, s);
    // assign value to shared_ptr
    value = std::shared_ptr<StringPtr>((new StringPtr(s.c_str())));
    //proccess value by reference
    procText(value);
    std::cout << "Value lowercased: " << value->str() << "\n";
    // print out value
    printReversed(value);
    return 0;
}
