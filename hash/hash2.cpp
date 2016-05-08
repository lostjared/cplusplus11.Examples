/*
 Example of C++11 hash table
 written by Jared Bruni
 
 http://objective-c.info
 */

#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>


class UserID {
public:
    UserID() = default;
    UserID(std::string name, unsigned int index) : user_name{name}, user_index{index} {
        
    }
    void setID(std::string name, unsigned int index) {
        user_name = name;
        user_index = index;
    }
    const int index() const { return user_index; }
    const std::string name() const { return user_name; }
    
    bool operator<(const UserID &u) {
        if(user_name<u.user_name) return true;
        return false;
    }
    
private:
    std::string user_name;
    unsigned int user_index;
};

class UserID_Compare {
public:
    bool operator()(const UserID &u1, const UserID &u2) const {
        if(u1.name()==u2.name() && u1.index()==u2.index()) return true;
        return false;
    }
};

class UserID_Hash {
public:
    size_t operator()(const UserID &u) const {
        return std::hash<std::string>()(u.name()) ^ std::hash<unsigned int>()(u.index());
    }
};


class Table {
public:
    
    Table() = default;
    
    void printOutAllItems(std::ostream &out) {
        for(auto i = map.begin(); i != map.end(); ++i) {
            out << i->first.name() << ":" << i->first.index() << ":" << i->second << "\n";
        }
    }
    
    std::string &operator[](const UserID &u) {
        return map[u];
    }
    
    size_t size() { return map.size(); }
    
private:
    std::unordered_map<UserID, std::string, UserID_Hash, UserID_Compare> map;
};

int main(int argc, char **argv) {
    Table hash_table;
    unsigned int id = static_cast<unsigned int>(time(0));
    for(;;) {
        std::cout << "Enter persons name to add/edit phone number to hash table (quit to exit): ";
        std::string s;
        std::getline(std::cin, s);
        if(s == "quit") break;
        std::cout << "Enter persons phone number: ";
        std::string s2;
        std::getline(std::cin, s2);
        hash_table[UserID(s,id)] = s2;
    }
    std::string fname;
    std::cout << "Enter file name: ";
    std::getline(std::cin, fname);
    std::fstream file;
    file.open(fname, std::ios::out);
    if(!file.is_open()) {
        std::cerr << "Could not open file..!\n";
        return 1;
    }
    hash_table.printOutAllItems(file);
    file.close();
    hash_table.printOutAllItems(std::cout);
    if(hash_table.size()==0) return 0;
    std::string name;
    std::cout << "Enter name for quick lookup: ";
    std::getline(std::cin, name);
    std::cout << name << "\'s phone number is: " << hash_table[UserID(name, id)] << "\n";
    return 0;
}