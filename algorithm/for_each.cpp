
/* for_each example */

#include<iostream>
#include<algorithm>
#include<vector>


void proc_elem(int value) {
    std::cout << "Value is: " << value << "\n";
}

int main() {
    
    std::vector<int> values { 0, 1, 99, 48, 64, 2, 1 };
    std::sort(values.begin(), values.end());
    std::for_each(values.begin(), values.end(), proc_elem);
    std::for_each(values.begin(), values.end(), [](int value) {
            std::cout << "Lambda value: " << value << "\n";
    });
    return 0;
}