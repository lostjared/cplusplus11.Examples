//
//  Created by Jared Bruni on 7/12/13.


#include<iostream>
#include<string>

class cxObject {
  
public:
    signed int cx, cy, cw, ch, color, direction;
    cxObject() = default;
    const cxObject &operator+(const cxObject &c) {
        cx += c.cx;
        cy += c.cy;
        cw += c.cw;
        ch += c.ch;
        color = c.color;
        return *this;
    }
    
};

class cyObject {

public:
    enum class Color { red, green, blue } color;

    cyObject() = default;
    cyObject(const cxObject  &c) {
        setColor(c);
    }
    void setColor(const cxObject &c) {
        switch(c.color) {
            case 0:
                color = Color::red;
                break;
            case 1:
                color = Color::green;
                break;
            case 2:
                color = Color::blue;
                break;
        }
    }
    
    Color operator+(const cxObject &c) {
        setColor(c);
        return color;
    }
};


template<typename T1, typename T2>
auto Return_Color(T1 t1, T2 t2) -> decltype(t2+t1) {
    return t2+t1;
}

std::ostream &operator<<(std::ostream &out, cyObject::Color c) {
    switch(c) {
        case cyObject::Color::red:
            out << "Red ";
            break;
        case cyObject::Color::green:
            out << "Green ";
            break;
        case cyObject::Color::blue:
            out << "Blue ";
            break;
    }
    return out;
}

int main(int argc, char **argv) {
    
    cxObject cx;
    cyObject cy;
    
    auto c = Return_Color<cxObject, cyObject>(cx, cy);
    std::cout << c << "\n";
    cx.color = 2;
    auto color_type = Return_Color<cxObject, cyObject>(cx, cy);
    std::cout << color_type << "\n";
    return 0;
    
}