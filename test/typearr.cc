/* 
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<iomanip>
#include<vector>


namespace mx {
    
    template<typename S, typename L>
    class TypeArray {
        static_assert(sizeof(S)<sizeof(L), "S larger then L");
        static_assert((sizeof(L)%sizeof(S)==0), "S cannot fit in L");
    public:
        TypeArray() : arr_index{} {}
        TypeArray(L l) : arr_index{l} {}
        TypeArray(const TypeArray<S,L> &t) : arr_index{t.arr_index} {}
        
        S &operator[](unsigned int i) {
            return arr[i];
        }
        
        TypeArray<S,L> &operator=(L l) {
            arr_index = l;
            return *this;
        }
        
        TypeArray<S,L> &operator=(const TypeArray<S,L> &t) {
            arr_index = t.arr_index;
            return *this;
        }
        
        L &value() { return arr_index; }
        size_t size() { return sizeof(L)/sizeof(S); }

    protected:
        union {
            S arr[sizeof(L)/sizeof(S)];
            L arr_index;
        };
        
    };
    
    typedef TypeArray<unsigned char, unsigned int> Color4;
    
    template<typename S, typename L>
    std::ostream &operator<<(std::ostream &out, TypeArray<S,L> &t) {
        out << "array { ";
        for(unsigned int i = 0; i < t.size(); ++i)
            out << std::setw(10) << static_cast<L>(t[i]) << " ";
        out << " }\n Large value: " << std::setw(15) << t.value() << "\n";
        return out;
    }
}


int main(int argc, char **argv) {
    mx::TypeArray<unsigned char, unsigned int> typearr(0xFFFFFF);
    std::cout << typearr << "\n";
    mx::TypeArray<unsigned char, unsigned long long> longarr(0x0F0F0F0F0F0FL);
    std::cout  << longarr << "\n";
    mx::Color4 v(0xFF01);
    std::cout << v << "\n";
    mx::TypeArray<unsigned int, unsigned long long> arr(0xFFFF0000FF);
    std::cout << arr << "\n";
// mx::TypeArray<std::vector<char>, char> bad;
// above line would cause compile time error
    
    return 0;
}
