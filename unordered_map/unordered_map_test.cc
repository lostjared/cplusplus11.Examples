//  Created by Jared Bruni on 7/14/13.
//  Trying out unordered map

#include<iostream>
#include<unordered_map>
#include<algorithm>
// Simple class

class Id {
public:
    std::string user;
    unsigned int id;
    Id() : user{}, id{} {
        
    }
    Id(std::string user) {
        setUser(user);
    }
    void setUser(std::string u) {
        static unsigned int off = 0;
        user = u;
        id = ++off;
    }
};

std::ostream &operator<<(std::ostream &out, const Id &i) {
    out << "User ID: " << i.user << ":" << i.id << "\n";
    return out;
}

void output_map(std::unordered_map<std::string, Id> &m) {
    auto print = [&](std::pair<std::string, Id> p) {
        std::cout << "Key: " << p.first << " value " << p.second;
    };
    for_each(m.begin(), m.end(), print);
}

int main(int argc, char **argv) {
    try {
        std::unordered_map<std::string, Id> user_map;
        for(std::string s : {"Jared", "Test", "Key"}) {
            user_map[s].setUser(s);
        }
        
        output_map(user_map);

        // or output

        std::cout << user_map["Jared"] << "\n";
        
        // or output this way
        
        for(auto &s : user_map) {
            std::cout << s.second;
        }
        
        // or create it this way
        std::unordered_map<std::string, std::string> test_map = {{"Test", "Value"}, {"Test2", "Value2"}, {"Jared", "MyValue"}};
        
        std::cout << "Value of Jared = "<< test_map["Jared"] << "\n";
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    } catch(...) {
        std::cerr << "Unknown Exception.\n";
    }
    
    return 0;
}
