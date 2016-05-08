/*
 
 operator overloading example
 written by Jared Bruni
 http://objective-c.info

*/


#include<iostream>
#include<string>
#include<sstream>

// class containing overloaded operators
class Text {
public:
    Text() = default;
    Text(std::string t) : text(t) {}
    
    Text &operator=(const std::string &t);
    Text operator+(const std::string &t);
    Text operator+(const Text &t);
    Text operator+(const int& x);
    
    
    // overloaded stream operator
    friend std::ostream &operator<<(std::ostream &out, const Text &t);
protected:
    std::string text;
    
};

Text &Text::operator=(const std::string &t) {
    text = t;
    return *this;
}

Text Text::operator+(const std::string &t) {
    Text temp;
    temp.text += text+t;
    return temp;
}

Text Text::operator+(const Text &t) {
    Text temp;
    temp.text = text+t.text;
    return temp;
}

Text Text::operator+(const int &x) {
    std::ostringstream stream;
    Text temp;
    stream << text << x;
    temp.text = stream.str();
    return temp;
}

std::ostream &operator<<(std::ostream &out, const Text &t) {
    out << t.text;
    return out;
}

int main(int argc, char **argv) {
    // print some example strings out
    Text t("Hello");
    Text value;
    value = t+" World";
    std::cout << value << "\n";
    Text e(" !");
    value = t+" World"+e;
    std::cout << value << "\n";
    value = t+" and Number: "+10;
    std::cout << value << "\n";
    return 0;
}