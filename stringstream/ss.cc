/*
*
*  C++11 Example
*  how to use: stringstream
*  http://objective-c.info
*/



#include<iostream>
#include<string>
#include<sstream>


// output to stdout
void out(const std::string &text) {
    std::cout << text << "\n";
}


int main(int argc, char **argv) {
    int x = 100;
    std::string text="hello world\n";
    std::ostringstream stream;
    // write to stream
    stream << "Value of integer: " << x << "\nValue of string: " << text;
    // output as string
    out(stream.str());
    stream << " added value\n";
    // convert to string
    std::string t = stream.str();
    std::cout << t << "\n";
    
    // other way around convert from string to text
    std::istringstream input("100 100");
    int y = 0, z = 0;
    // scan from string
    input >> y >> z;
    // add to integers
    y += 10;
    z += 10;
    // output to stdout
    std::cout <<  y << ":" << z << "\n";
    return 0;
}