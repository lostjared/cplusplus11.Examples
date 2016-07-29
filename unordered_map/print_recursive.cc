//  recursion
//  Created by Jared Bruni on 7/14/13.

#include<iostream>
#include<unordered_map>
#include<string>
#include<sstream>
#include<algorithm>

void PrintMap(std::unordered_map<std::string, std::string> &m, std::unordered_map<std::string, std::string>::iterator map_iterator) {

    std::cout << map_iterator->first << ": " << map_iterator->second;
    
    map_iterator++;
    if(map_iterator == m.end())
        return;

    PrintMap(m, map_iterator); // recursive
}


int main(int argc, char **argv) {
    std::unordered_map<std::string, std::string> test;
    for (auto s : { "String1", "String2", "Jared", "Adding Stuff", "To the Map" }) {
        std::ostringstream stream;
        stream << s << ": is the value here\n";
        test[s] = stream.str();
    }
    // print map with recursion
    
    PrintMap(test, test.begin());
    
    // print a string
    
    std::cout << test["String1"] << " \n";
    return 0;
}
