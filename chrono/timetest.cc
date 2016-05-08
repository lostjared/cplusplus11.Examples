/*
 written by Jared Bruni
 http://lostsidedead.com
 
*/

#include<iostream>
#include<chrono>

template<size_t X, size_t Y>
void WasteTime() {
    for(size_t i = 0; i < X; ++i) {
        for(size_t z = 0; z < Y; ++z) {
                std::cout << "Waste some time " << i << ":" << z << " \n";
        }
    }
}

int main(int argc, char **argv) {
    using namespace std;
    auto n1 = chrono::high_resolution_clock::now();
    WasteTime<400, 400>();
    auto n2 = chrono::high_resolution_clock::now();
    
    std::cout << "Operation WasteTime took " << chrono::duration_cast<chrono::milliseconds>(n2-n1).count() << " milliseconds\n";
    
    
    return 0;
}