/*
 emplace
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<string>
#include<vector>
#include<cctype>

class UserInfo {
public:
    std::string first, last;
    unsigned int id;
    UserInfo() = default;
    UserInfo(std::string f, std::string l, unsigned int i) : first{f}, last{l}, id{i} {}
    
    std::string::iterator findFirst(std::string::iterator start, std::string::iterator stop) {
        std::string::iterator i;
        for(i = start; i != stop; ++i) {
            if(isalpha(*i))
                return i;
        }
        return start;
    }
    
    void capitalize() {
        
        if(first.length()>0) {
            std::string::iterator i = findFirst(first.begin(), first.end());
            *i = toupper(*i);
        }
        if(last.length()>0) {
            std::string::iterator i = findFirst(last.begin(), last.end());
            *i = toupper(*i);
        }
    }
};

std::istream &operator>>(std::istream &in, UserInfo &user) {
    in >> user.first >> user.last;
    return in;
}

std::ostream &operator<<(std::ostream &out, UserInfo &user) {
    out << user.last << ", " << user.first << " ";
    return out;
}

int main(int argc, char **argv) {
    
    std::vector<UserInfo> v;

    // build UserInfo from arguments supplied to this member function
    v.emplace_back("Jared", "Bruni", 101);
    
    char yn = 'Y';
    do {
        UserInfo u;
        std::cout << "Enter user name First Last: ";
        std::cin >> u;
        u.capitalize();
        v.push_back(u);
        std::cout << "Enter another Y/N: ";
        std::cin >> yn;
        
    } while (toupper(yn) == 'Y' && !std::cin.eof());
    
    
    std::cout << "Values entered into vector: \n";
    
    for(auto &i : v) {
        std::cout << i << "\n";
    }
    
    return 0;
}