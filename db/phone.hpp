#ifndef __PHONE__H_
#define __PHONE__H_
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

namespace db {
    class PhoneRecord {
    public:
        PhoneRecord();
        PhoneRecord(std::string first, std::string last, std::string number);
        bool operator<(const PhoneRecord &p) const;
        std::string first, last, number;
    };
    
    
    PhoneRecord::PhoneRecord() {}
    
    PhoneRecord::PhoneRecord(std::string f, std::string l, std::string n) : first{f}, last{l},number{n} {}
    
    bool PhoneRecord::operator<(const PhoneRecord &p) const {
        return (last<p.last);
    }
    
    std::ostream &operator<<(std::ostream &out, PhoneRecord &r) {
        out  << r.first << " " << r.last << " 's Number is: " << r.number;
        return out;
    }

    
    class PhoneDB {
    public:
        PhoneDB(std::string filename);
        ~PhoneDB();
        void loadRecords(std::string filename);
        void saveRecords(std::string filename);
        void addRecord(std::string first, std::string last, std::string number);
        PhoneRecord &operator[](unsigned int pos);
        bool findByName(std::string first, std::string last, PhoneRecord &p);
        void printNumbers(std::ostream &out);
        void sort();
    protected:
        std::vector<PhoneRecord> numbers;
        std::string fname;
    };
    
    PhoneDB::PhoneDB(std::string filename) : fname{filename} {
        loadRecords(filename);
    }

    PhoneDB::~PhoneDB() {
        saveRecords(fname);
    }

    void PhoneDB::loadRecords(std::string filename) {
        if(!numbers.empty()) {
            numbers.erase(numbers.begin(), numbers.end());
        }
        std::fstream file;
        file.open(filename, std::ios::in);
        if(!file.is_open()) return;
        while(!file.eof()) {
            std::string first, last, number;
            std::getline(file, first);
            std::getline(file, last);
            std::getline(file, number);
            
            if(number.length() > 0 && last.length() > 0 && first.length() > 0) {
                PhoneRecord r(first, last, number);
                numbers.push_back(r);
            }
        }
        file.close();
    }
    
    void PhoneDB::saveRecords(std::string filename) {
        std::fstream file;
        file.open(filename, std::ios::out);
        for(int i = 0; i < numbers.size(); ++i) {
            file << numbers[i].first << "\n" << numbers[i].last << "\n" << numbers[i].number << "\n";
        }
        file.close();
    }
    
    
    void PhoneDB::addRecord(std::string first, std::string last, std::string number) {
        PhoneRecord r(first,last,number);
        
        for(int i = 0; i < numbers.size(); ++i)
            if(numbers[i].last==last && numbers[i].first==first) return;
        
        numbers.push_back(r);
        sort();
    }
    
    PhoneRecord &PhoneDB::operator[](unsigned int pos) {
        return numbers[pos];
    }

    bool PhoneDB::findByName(std::string first, std::string last, PhoneRecord &p) {
        for(int i = 0; i < numbers.size(); ++i) {
            if(numbers[i].last==last && numbers[i].first==first) {
                p = numbers[i];
                return true;
            }
        }
        return false;
    }
    
    void PhoneDB::printNumbers(std::ostream &out) {
        for(auto &i : numbers) {
            out << i << "\n";
        }
    }
    
    void PhoneDB::sort() {
        std::sort(numbers.begin(), numbers.end());
    }
}

#endif
