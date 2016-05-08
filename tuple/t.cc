/*
 written by Jared Bruni
 http://lostsidedead.com
*/


#include<iostream>
#include<tuple>
#include<string>
#include<sstream>
#include<vector>
#include<iomanip>
// use a tuple to return multiple return values
std::tuple<std::string, int,std::string> grabPhoneNumber() {
    std::string temp;
    std::cout << "enter name: ";
    std::cin >> temp;
    int zipcode=0;
    std::cout << "enter zipcode: ";
    std::cin >> zipcode;
    std::string number;
    std::cout << "enter phone number: ";
    std::cin >> number;
    return std::make_tuple(temp,zipcode,number);
}


int main(int argc, char **argv) {
    // grab phone number
    auto info = grabPhoneNumber();
    // print out data
    std::cout << std::setw(10) << std::get<0>(info) << ": " << std::setw(10) << std::get<1>(info) << " : " << std::setw(10) << std::get<2>(info) << "\n";
    // create a vector of tuples
    std::vector<std::tuple<std::string,int,std::string>> vec;
    vec.push_back(info);
    // add another one
    vec.push_back(std::make_tuple("Jared B",92126, "555-555-555"));
    // print out the vector
    std::cout << "Items in vector: {\n";
    const size_t vsize = vec.size();
    for(unsigned int i = 0; i != vsize; ++i) {
        std::cout << std::get<0>(vec[i]) << "\n";
    }
    std::cout << "}\n";
    // create a tuple containing 4 items
    std::tuple<std::string,std::vector<std::string>,std::vector<int>, int> vtuple;
    
    for(int i = 0; i < 24; ++i) {
        std::ostringstream stream;
        stream << "Value: " << i;
        // add to vector
        std::get<1>(vtuple).push_back(stream.str());
    }
    const size_t sizeval = std::get<1>(vtuple).size();
    for(unsigned int i = 0; i != sizeval; ++i) {
        std::cout << "Value: " << std::get<1>(vtuple)[i] << "\n";
    }
    return 0;
}