#include "code.hpp"

namespace interp {
    
    // Text Line 
    
    TextLine::TextLine() : index(0), text("") {}
    
    TextLine::TextLine(int index, std::string text)
    {
        this->index = index;
        this->text = text;
    }
    
    TextLine::TextLine(const TextLine &t) {
        index = t.index;
        text = t.text;
    }
    bool TextLine::operator<(const TextLine &t) const {
        return (index < t.index);
    }
    
    bool TextLine::operator==(const TextLine &t1) const {
        return (index == t1.index);
    }
    TextLine &TextLine::operator=(const TextLine &t) {
        index = t.index;
        text = t.text;
        return *this;
    }
    
    // Code
    
    void Code::clear() {
        
    }
    
    
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
            if(in.length()==0) continue;
            std::vector<lex::Token> tokens;
            std::istringstream stream(in);
            lex::Scanner scan(stream);
            while(scan.valid()) {
                lex::Token token;
                scan >> token;
                tokens.push_back(token);
            }
            inputText(tokens, in);
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
    
    void inputText(std::vector<lex::Token> &tokens, std::string input_line) {
        if(tokens.size()>=2 && input_line.length()>0) {
            lex::Token_type num = tokens[0].getTokenType();
            if(num != lex::TOKEN_DIGIT) {
                std::cerr << "Requires line number before code.\n";
                return;
            }
            int value = atoi(tokens[0].getToken().c_str());
            std::string codetext;
            codetext = input_line.substr(input_line.find(tokens[0].getToken())+tokens[0].getToken().length()+1, input_line.length());
            TextLine in(value, codetext);
            insertText(in);
        } else {
            std::cerr << "Error invalid input.\n";
            return;
        }
    }
    
    bool procLine(const TextLine &text, Code &code) {
        std::istringstream input(text.text);
        lex::Scanner scan(input);
        std::vector<lex::Token> tokens;
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            tokens.push_back(token);
        }
        // for now output each token
        std::cout << "Code Line: ["<<text.index <<"] - [" << text.text << "] = {\n";
        for(unsigned int i = 0; i < tokens.size(); ++i) {
            std::cout << tokens[i] << "\n";
        }
        std::cout << "}\n\n";
        return true;
    }
    
}
