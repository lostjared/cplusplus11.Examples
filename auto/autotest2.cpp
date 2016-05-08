#include<iostream>
#include<vector>

// C++11 requires the ->
// C++14 auto by itself is valid also decltype(auto)
template<typename It>
auto Output(It start, It stop) -> void {
    for(It i =start; i!=stop; ++i) {
        std::cout << *i << "\n";
    }
}

template<typename T>
void PrintBackwards(std::vector<T> &vec) {

    for(auto i = vec.rbegin(); i != vec.rend(); ++i)
        std::cout << "Reversed: " << *i << "\n";
    
}
        
        
int main(int argc, char **argv) {
    
    std::cout << "Enter 3 integers: ";
    
    std::vector<int> vec;
    for(int i = 0; i < 3; ++i) {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }
    
    // auto for foreach
    for(auto &it : vec) {
        std::cout << it << "\n";
    }
    
    
    // without auto
    std::vector<int>::iterator start,stop;
    start = vec.begin();
    stop =  vec.end();
    Output(start, stop);
   
    // with auto much easier to type
    auto i = vec.begin(), z = vec.end();
    Output(i, z);
    
    // traverse is reverse order
    PrintBackwards(vec);
    
    
    
    return 0;
}