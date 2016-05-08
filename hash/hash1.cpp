/* unordered_map hash example
 
 written by Jared Bruni
 http://objective-c.info
 
*/


#include<iostream>
#include<unordered_map>
#include<string>

class UserName {
public:
    UserName(std::string username, std::string useremail) : my_username(username), my_email(useremail) {}
    UserName() = default;
    
    const std::string user() const { return my_username; }
    const std::string email() const { return my_email; }
    
    std::string my_username, my_email;
};

class UserName_Hash {
public:
    size_t operator()(const UserName &u) const {
        return std::hash<std::string>()(u.user()) ^ std::hash<std::string>()(u.email());
    }
};

class UserName_Compare {
public:
    bool operator()(const UserName &u1, const UserName &u2) const {
        if(u1.user()==u2.user() && u1.email()==u2.email()) return true;
        return false;
    }
};

std::istream &operator>>(std::istream &in, UserName &u) {
    in >> u.my_username >> u.my_email;
    return in;
}

std::ostream &operator<<(std::ostream &out, const UserName &u) {
    out << u.user() << ":" << u.email();
    return out;
}

int main(int argc, char **argv) {
    
    std::unordered_map<UserName,std::string, UserName_Hash, UserName_Compare> users;
    while(1) {
        std::cout << "Enter phone number (quit to exit):";
        std::string input;
        std::cin >> input;
        if(input == "quit") break;
        UserName u;
        std::cout << "Enter username/email: ";
        std::cin >> u;
        users[u] = input;
    }
    
    std::cout << "Inputed numbers..\n";
    for(auto i = users.begin(); i != users.end(); ++i) {
        const UserName &u = i->first;
        std::cout << u << ": " << i->second << "\n";
    }
    
    return 0;
}