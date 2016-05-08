/* sort example
   written by Jared Bruni
  http://lostsidedead.com
 
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

int main(int argc, char **argv) {

    std::vector<std::string> strings;
    
    for(;;) {
        std::cout << "Enter string (quit to exit and sort):";
        std::string s;
        std::getline(std::cin,s);
        if(s=="quit") break;
        strings.push_back(s);
    }
    
    std::sort(strings.begin(), strings.end());
    
    std::cout << "Sorted..\n";
    
    for(auto &i : strings) {
        std::cout << i << "\n";
    }
    
    return 0;
}
