/* 
 
 
 Line Sort - Practice
 
 Enter digit then text like on old 8 bit machines
 
 > 10 hey
 > 20 test
 > 30 here
 
 enter list to display
 
 > @list
 
 > @quit
 to exit
 
 > @save filename
 > @open filename
 > @clear
 > @remove
 
 */

#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<fstream>

void inputText(std::string text);

class TextLine {
public:
    TextLine(int index, std::string text) { this->index = index; this->text = text; }
    bool operator<(const TextLine &t) const {
        return (index < t.index);
    }
    
    bool operator==(const TextLine &t1) const {
        return (index == t1.index);
    }
    TextLine &operator=(const TextLine &t) {
        index = t.index;
        text = t.text;
        return *this;
    }
    int index;
    std::string text;
};

std::vector<TextLine> lines;

bool saveLineSource(const std::string &text) {
    std::fstream file;
    file.open(text, std::ios::out);
    if(!file.is_open()) return false;
    for(unsigned int i = 0; i < lines.size(); ++i) {
        file << lines[i].index << " " << lines[i].text << "\n";
    }
    file.close();
    return true;
}

bool openLineSource(const std::string &text) {
    std::fstream file;
    file.open(text, std::ios::in);
    if(!file.is_open()) return false;
    
    if(!lines.empty()) {
        lines.erase(lines.begin(), lines.end());
    }
    
    while(!file.eof() && file) {
        std::string in;
        std::getline(file,in);
        inputText(in);
    }
    file.close();
    return true;
}

void insertText(const TextLine &in) {
    for(unsigned int i = 0; i < lines.size(); ++i) {
        if(lines[i].index == in.index) {
            lines[i].text = in.text;
            return;
        }
    }
    lines.push_back(in);
    std::sort(lines.begin(), lines.end());
}

void inputText(std::string input_line) {
    std::string sep;
    int pos = input_line.find(" ");
    if(pos == std::string::npos) return;
    sep = input_line.substr(0,pos);
    int num = atoi(sep.c_str());
    if(num == 0) {
        std::cerr << "Invalid line number.\n";
        return;
    }
    std::string text = input_line.substr(pos, input_line.length()-pos);
    TextLine in(num, text);
    insertText(in);
}

int main() {
    bool active = true;
    while(active) {
        std::cout << "> ";
    	std::string input_line;
        std::getline(std::cin, input_line);
        if(input_line == "@quit") break;
        else if(input_line == "@list") {
            for(auto i = lines.begin(); i != lines.end(); ++i) {
                std::cout << i->index << ": " << i->text << "\n";
            }
            continue;
        } else if (input_line.find("@save ") != std::string::npos) {
            std::string filename;
            filename = input_line.substr(input_line.find(" ")+1, input_line.length());
            saveLineSource(filename);
            continue;
        } else if(input_line.find("@open ") != std::string::npos) {
            std::string filename;
            filename = input_line.substr(input_line.find(" ")+1, input_line.length());
            openLineSource(filename);
            continue;
        } else if(input_line == "@clear") {
            if(!lines.empty()) {
                lines.erase(lines.begin(), lines.end());
            }
            continue;
        } else if(input_line.find("@remove ") != std::string::npos) {
            std::string index;
            index = input_line.substr(input_line.find(" ")+1, input_line.length());
            int in = atoi(index.c_str());
            if(in <= 0) {
                std::cerr << "Error: requires index.\n";
                continue;
            }
            for(unsigned int i = 0; i < lines.size(); ++i) {
                if(lines[i].index == in) {
                    lines.erase(lines.begin()+i);
                    break;
                }
            }
            std::cout << "Line: " << in << " removed..\n";
            continue;
        }
        inputText(input_line);
    }
    return 0;
}
