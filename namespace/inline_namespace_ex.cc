//  Created by Jared Bruni on 7/15/13.
// inline namespace

#include<iostream>
#include<sstream>
#include<vector>

namespace mx {
    
    inline namespace ver1 {
        
        void sayHello() {
            std::cout << "Hello from Version 1\n";
        }
        
        std::vector<std::string> split(std::string text) {
            sayHello();
            std::vector<std::string> splitType;
            std::istringstream stream(text);
            for(std::string s; stream >> s;)
                splitType.push_back(s);
            
            return splitType;
        }
    }
    
    namespace ver2 {
        
        void sayHello() {
            std::cout << "Hello from Version 2\n";
        }
        
        template<typename Type = std::string>
        std::vector<Type> split(std::string text) {
            sayHello();
            std::vector<Type> vType;
            std::istringstream stream(text);
            for(Type t; stream >> t;)
                vType.push_back(t);
            return vType;
        }
    }
}

int main(int argc, char **argv) {
    
    
    using std::string;
    using std::vector;
    using std::getline;
    using std::cerr;
    using std::cout;
    using std::cin;
    
    using namespace mx;
    
    try {
        
        sayHello();
        
        using ver2::sayHello;
        
        sayHello();
        
        cout << "Enter string seperated by spaces\n ";
        string text;
        
        getline(cin, text);
        vector<string> v;
        v = split(text);
        
        for(auto &s : v) {
            cout << "Token: " << s << "\n";
        }
        
        cout << "Enter another string seperated by spaces\n";
        getline(cin, text);
        vector<string>  vec2;
        
        using ver2::split;
        
        vec2 = split(text);
        
        for(auto &st : vec2) {
            cout << "Gen Token: " << st << "\n";
        }
    } catch(std::exception &e) {
        cerr << "Error: " << e.what() << "\n";
    } catch(...) {
        cerr << "Unhandled error\n";
    }
    
    return 0;
    
}