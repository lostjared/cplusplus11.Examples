/* C++11 example
   example using istringstream
   this program takes one argument that being a integer value
   it will convert to a integer if its not a valid value it will print
   invalid value
*/
 

#include<iostream>
#include<string>
#include<sstream>
#include<cctype>

class InvalidInput {};
// use a input string stream to convert the string to a integer
// there are a ton of different ways you can do this
// this is just one of them, others include atoi lexical_cast etc.
int convertInteger(std::string text) {
    int val = 0;
    std::istringstream stream(text); // use stream just like you would std::cin
    stream >> val;
    if(stream.fail())
        throw InvalidInput();
    
    return val;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Requires one argument..\n";
        return -1;
    }
    try {
        int value = convertInteger(argv[1]);
        std::cout << "Value is: " << value << "\n";
        std::cout << value << " + 255 is: " << value+255 << "\n";
    } catch(InvalidInput &e) {
        std::cout << "Invalid input.\n";
    }
    return 0;
}