/* written by Jared Bruni
 http://lostsidedead.com
 
 */

#include<iostream>

template<typename StrType>
class User {
public:
    User() : first{}, last{}, middle{} {}
    User(StrType s_first, StrType s_last, StrType s_middle) : first{s_first}, last{s_last}, middle{s_middle} {}
    
    StrType &firstName() { return first; }
    StrType &lastName()  { return last; }
    StrType &middleName(){ return middle; }
protected:
    StrType first, last,middle;
};

template<typename T>
class UserName : public User<T> {
public:
    UserName(T first, T last, T middle) : User<T>(first,last,middle) {}
    template<typename T2>
    void printName(T2 &out)  {
        out << this->firstName() << ", " << this->lastName() << " , " << this->middleName()  << "\n";
    }
};


int main(int argc, char **argv) {
    
    UserName<std::string> name("Jared", "Bruni", "P");
    UserName<std::wstring> name2(L"Jared", L"Bruni", L"p");

    name.printName(std::cout);
    name2.printName(std::wcout);
    
    return 0;
}