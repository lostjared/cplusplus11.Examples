/* 
 
 
 Line Sort - Practice
 
 Enter digit then text like on old 8 bit machines
 
 > 10 hey
 > 20 test
 > 30 here
 
 enter list to display
 
 > list
 
 > quit 
 to exit
 */



#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>

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

int main() {
    bool active = true;
    while(active) {
        std::cout << "> ";
    	std::string input_line;
        std::getline(std::cin, input_line);
        
        if(input_line == "quit") break;
        if(input_line == "list") {
            for(auto i = lines.begin(); i != lines.end(); ++i) {
                std::cout << i->index << ": " << i->text << "\n";
            }
        }
        std::string sep;
        int pos = input_line.find(" ");
        if(pos == std::string::npos) continue;
        sep = input_line.substr(0,pos);
        int num = atoi(sep.c_str());
        if(num == 0) {
            std::cerr << "Invalid line number.\n";
            continue;
        }
        std::string text = input_line.substr(pos, input_line.length()-pos);
        std::cout << text << ":" << num << "\n";
        TextLine in(num, text);
        insertText(in);
    }
    return 0;
}
