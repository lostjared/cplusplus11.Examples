/* Algorithm function transform test */


#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    std::cout << "Before: \n";
    std::vector<int> v1 {0,1,4,2,6,5,4};
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter: \n";
    std::vector<int> v2;
    std::transform(v1.cbegin(), v1.cend(), std::back_inserter(v2),[](int value) {
        return -value;
    });
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    return 0;
}