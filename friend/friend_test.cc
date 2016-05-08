/*

  friend test
 written by Jared Bruni
 http://lostsidedead.com

*/

#include<iostream>
#include<string>
#include<vector>


class Database;

class User {
    friend Database; // friend of class Database
    std::string first,last;
public:
    User(std::string f, std::string l) : first{f}, last{l} {
        std::cout << "Added User " << first << " " << last << ".\n";
    }
    friend std::ostream &operator<<(std::ostream &out, const User &u);
};

class Database {
public:
    Database() = default;
    void addUser(std::string first, std::string last) {
        users.push_back(User(first, last));
    }
    
    void printUsersLastFirst() {
        for(auto &i : users) {
            // class is a friend can access private members
            std::cout << "Username is: " << i.last << ", " << i.first << "\n";
        }
    }
protected:
    std::vector<User> users;
};
        
        
std::ostream &operator<<(std::ostream &out, const User &u) {
    out << u.first << " " << u.last << " "; // ok function is a friend
    // can access private members
    return out;
}


int main(int argc, char **argv) {
    
    try {
        Database d;
        d.addUser("Jared", "Bruni");
        d.addUser("Freddy", "Krueger");
        d.addUser("Jason", "Voorhees");
        d.printUsersLastFirst();
    }
    catch(...) {
        
    }
    return 0;
}
