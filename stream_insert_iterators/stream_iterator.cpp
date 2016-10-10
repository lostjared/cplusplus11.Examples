/* stream iterator test 
 
 Adapted from The C++ Stanard Library second edition
 
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

int main() {
    std::vector<std::string> value1;
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),std::back_inserter(value1));
    
    std::sort(value1.begin(), value1.end());
    // Unique
    std::cout << "Unique copy\n";
    std::cout << "Unique copy\n";
    std::unique_copy(value1.begin(), value1.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    // Standard Copy
    std::cout << "Standard Copy\n";
    std::copy(value1.begin(), value1.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "\n";
    // Copy Vector of int
    std::cout << "Copy Integers\n";
    std::vector<int> v {0,1,3,4,6};
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    return 0;
}
