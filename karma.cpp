#include<iostream>

// Energy type, contains the value
template<typename T>
class Energy {
public:
    Energy() = default; // default constructor

    Energy(const T &e) : energy{e} {
    
    }
    
    T& E()  {
        return energy;
    }
    
    int procCommand(const T &s) {
        if(s == love) return 1;
        if(s == fear) return 0;
        if(s == death) return -1;
        return 0;
    }
    
    void setKeys(const T &l, const T &f, const  T &d) {
        love = l;
        fear = f;
        death = d;
    }
    
protected:
    T energy;
    T love, fear, death;
};

// for this version
const std::string LOVE="love", FEAR="fear", DEATH="die";

// the Karma template, this processes the Energy
template<typename T>
class Karma {
public:
    Karma() = default;
    bool get(Energy<T> type) {
        int cmd = type.procCommand(type.E());
        switch(cmd) {
            case 0:
                std::cout << "Gave fear..\n";
                break;
            case 1:
                std::cout << "Gave love..\n";
                break;
            case -1:
                return false;
                break;
        }
        return true;
    }
    
    Energy<T> give() {
        std::cout << "Enter value: ";
        Energy<T> e;
        std::cin >> e.E();
        e.setKeys(LOVE, FEAR, DEATH);
        return e;
    }
    
protected:
    
};

// the Life class, creates a version of karma and then invokes it when birth is called
class Life {
public:
    Life() = default;
    void birth() {
        while(karma.get(karma.give())) {
            std::cout << "Karma cycle..\n";
        }
    }
    Karma<std::string> karma; // karma type using std::string
};
// the main function
int main(int argc, char **argv) {
    Life life;// life is created
    while(1) { // infinite loop
        std::cout << "New thought created..\n";
        life.birth();// another birth cycle
    }
    return 0;
}

