/* Wrapper using Initializer List */

#include<iostream>
#include<vector>
#include<string>
#include<initializer_list>
#include<algorithm>

template<typename T>
class VectorWrapper {
public:
    VectorWrapper() { }
    VectorWrapper(std::initializer_list<T> il) : v{il} {
        std::cout << "Wrapper Started..\n";
    }
    void addTo(T type) {
        // do something before adding to v
        v.push_back(type);
    }
    std::vector<T> &cont() { return v; }
protected:
    std::vector<T> v;
};


int main(int argc, char **argv) {

    VectorWrapper<std::string> wrap({"test ", "one", "two", "three"});
    for_each(wrap.cont().begin(), wrap.cont().end(), [](std::string s) {
        std::cout << "Element: " << s << "\n";
    });
    
    return 0;
}
