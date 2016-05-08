// example of lambda.
#include<iostream>
#include<vector>
#include<algorithm>

int main(int argc, char **argv) {
    std::vector<unsigned int> v = { 0, 4, 6, 24, 10, 7, 3, 1 };
    std::for_each(v.begin(), v.end(), [](unsigned int value) {
        std::cout << "Current Value is: " << value << "\n";
    });
    std::sort(v.begin(), v.end());
    for(auto &elem : v) {
        std::cout << "New  Sorted Value is: " << elem << "\n";
    }
}