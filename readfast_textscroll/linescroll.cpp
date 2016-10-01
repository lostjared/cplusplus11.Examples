/* Written by Jared Bruni 
   http://lostsidedead.com
 
 "Open Source, Open Mind"
 
*/

#include<iostream>
#include<string>
#include<fstream>
#include<thread>
#include<chrono>

int main(int argc, char **argv) {
    if(argc == 3) {
        std::fstream input;
        input.open(argv[1], std::ios::in);
        if(!input.is_open()) {
            std::cerr << "Could not open file: " << argv[1] << "\n";
            exit(0);
        }
        int mill = atoi(argv[2]);
        if(mill < 0) {
            std::cerr << "Error invalid delay\n";
            exit(0);
        }
        while(!input.eof()) {
            std::string text;
            std::getline(input, text);
            if(input) {
                 for(auto start = text.begin(); start != text.end(); ++start) {
                    std::cout << *start;
                    fflush(stdout);
                    std::this_thread::sleep_for(std::chrono::milliseconds(mill));
                 }
            }
            std::cout << "\n";
        }
        input.close();
    } else {
        std::cerr << "Requires two arguments...\nlinescroll source delay\n";
        exit(0);
    }
    return 0;
}
