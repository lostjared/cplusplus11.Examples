//
//  main.cpp
//  CxxTest
//
//  Created by Jared Bruni on 7/8/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//

#include<iostream>
#include<string>
#include<map>
#include<algorithm>

template<typename var_type>
class SymbolTable {
public:
    SymbolTable() = default;
    SymbolTable(const SymbolTable &t) = delete;
    
    void operator=(const SymbolTable &t) = delete;
    var_type &get_Symbol(std::string s) { return vars[s]; }
  
    template<typename F>
    void proc_Items(F f) {
        std::for_each(vars.begin(), vars.end(), f);
    }
    std::map<std::string, var_type> &cont() { return vars; }
protected:
    std::map<std::string, var_type> vars;
    
};

class Color {
public:
    Color() = default;
    Color(const Color &c) {
        copyRGB(c);
    }
    void operator=(const Color &c) {
        copyRGB(c);
    }
    

    friend std::ostream &operator<<(std::ostream &out, Color &c);
    unsigned char &operator[](unsigned int i) { return rgb[i]; }
    union C {
        unsigned char value[4];
        unsigned int total_value;
    };
    
    void setColor(unsigned int color) {
        static_assert( sizeof(unsigned char) == 1, "Unsigned char larger than byte");
        static_assert( sizeof(unsigned int) == 4, "unsigned int not 4 bytes");
        C c;
        c.total_value = color;
        for(signed int i = 0; i < 4; ++i)
            rgb[i] = c.value[i];
        
    }

    unsigned int toInteger() {
        static_assert( sizeof(unsigned char) == 1, "Unsigned char larger than byte");
        static_assert( sizeof(unsigned int) == 4, "unsigned int not 4 bytes");
        C c;
        for(signed int i = 0; i < 4; ++i) {
            c.value[i] = rgb[i];
        }
        return c.total_value;
    }
    
protected:
    unsigned char rgb[4];
    
    void copyRGB(const Color &c) {
        for(signed int i = 0; i < 4; ++i) {
            rgb[i] = c.rgb[i];
        }
    }
};

std::ostream &operator<<(std::ostream &out, Color &c) {
    out << "Value : " << c.toInteger() << "\n";
    return out;
}


int main(int argc, char **argv) {
    
    try {
        SymbolTable<std::string> st;
        SymbolTable<Color> colors;
        std::cout << "Input variable: ";
        for(std::string value; std::cin>>value;) {
            if(value == "quit") break;
            std::string value1;
            std::cout << "Set value: ";
            std::cin>>value1;
            int color_value = atoi(value1.c_str());
            Color &c = colors.cont()["value 1"];
            c.setColor(color_value);
            st.get_Symbol(value) = value1;
            st.proc_Items([](std::pair<std::string, std::string> p)
            { std::cout << p.first << " := " << p.second << "\n"; });
            std::cout << "Input variable: ";
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error\n";
    }

    return 0;
}
