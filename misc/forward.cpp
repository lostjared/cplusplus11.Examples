// from page 207 from Effective Modern C++

#include<iostream>
#include<vector>

// function to be called from fwd template
void passed(const std::vector<int> &v) {
    for(auto &i : v) {
        std::cout << i << ",";
    }
    std::cout << "\n";
}



// passes parameters to passed
template<typename... Ts>
void fwd(Ts&&... params) {
    passed(std::forward<Ts>(params)...);
}


int main(int argc, char **argv) {
    std::vector<int> values = {4,5,6};
    auto init_list = {1, 2, 3};
    fwd(init_list); // initalizer list
    fwd(values); // pass vector
    return 0;
}