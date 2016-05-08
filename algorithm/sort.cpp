/* Will ask for series of usernames
   then print out the sorted list by last name */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class User {
public:
    User(const std::string &f, const std::string &l) : first(f), last(l) {
        
    }
    User() { }
    std::string firstname() const { return first; }
    std::string lastname() const { return last; }
protected:
    std::string first, last;
};

int main() {
    char c;
    std::vector<User> users;
    
    do {
        std::cout << "Enter first name: ";
        std::string sf, sl;
        std::getline(std::cin, sf);
        std::cout << "Enter last name: ";
        std::getline(std::cin, sl);
        std::cout << "Do you wish to enter another name? y/n ";
        std::string sc;
        std::getline(std::cin, sc);
        c = sc[0];
        User u(sf,sl);
        users.push_back(u);
        
    } while(c == 'y' || c == 'Y');
    
    std::cout << "Sorted: \n";
    
    std::sort(users.begin(), users.end(), [](const User &u1, const User &u2) {
        return (u1.lastname()<u2.lastname());
    });
    
    for (auto &i : users) {
        std::cout << i.lastname() << ", " << i.firstname() << "\n";
    }
    
    return 0;
}