#include"phone.hpp"


void printMenu();
void procInput(int index);
std::string mustInput(std::istream &in);

db::PhoneDB database("db.txt");

int main() {
    int index = 0;
    do {
        printMenu();
        std::cout << "Enter Choice: ";
        std::string input;
        std::getline(std::cin, input);
        index = atoi(input.c_str());
        if(index >= 1 && index <= 3) procInput(index);
        
    } while(index != 4);
    
    std::cout << "Goodbye!\n";
    return 0;
}


void printMenu() {
    std::cout << "******\nPhoneDB by Jared.\nType 1 to Enter a Phone Number\nType 2 to Lookup a Phone Number\nType 3 to print out all Numbers.\nType 4 to Exit.\n******\n";
}

void procInput(int index) {
    std::string first, last, number;
    switch(index) {
        case 1: {
            std::cout << "Enter first name: ";
            first = mustInput(std::cin);
            std::cout << "Enter last name: ";
            last = mustInput(std::cin);
            std::cout << "Enter number: ";
            number = mustInput(std::cin);
            database.addRecord(first, last, number);
        }
            break;
        case 2: {
            std::cout << "Enter first name: ";
            first = mustInput(std::cin);
            std::cout << "Enter last name: ";
            last = mustInput(std::cin);
            db::PhoneRecord r;
            if(database.findByName(first, last, r) == true) {
                std::cout << r << "\n";
            }
        }
            break;
        case 3: {
            std::cout << "[----------------------------------]\n";
            database.printNumbers(std::cout);
            std::cout << "[----------------------------------]\n";
        }
            break;
    }
}

std::string mustInput(std::istream &in) {
    std::string s;
    std::getline(in, s);
    
    if(s.length() > 0) return s;
    else {
        std::cout << "Requires input try again...\n";
        return mustInput(in);
    }
    return s;
}