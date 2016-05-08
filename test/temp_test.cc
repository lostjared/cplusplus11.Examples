/* 
 templates as arguments
 written by Jared Bruni
 http://lostsidedead.com
 
 */

#include<iostream>
#include<vector>

namespace mx {
    
    template<typename T,template<typename> class C>
    class My_List  {
    public:
        My_List() {}
        My_List(std::initializer_list<T> t) : arr{t} {}
        void print();
        C<T> &container() { return arr; }
    protected:
        C<T> arr;
    };
    
    template<typename T, template<typename> class C>
    void My_List<T,C>::print() {
        for(auto &i : arr) {
            std::cout << "List value: " << i << "\n";
        }
    }
    
    template<typename T>
    using My_ListContainer = std::vector<T>;
}

// simple test of template
int main(int argc, char **argv) {
    mx::My_List<int,mx::My_ListContainer> list1({255, 1024, 2048, 4096});
    list1.print();
    return 0;
    
}