#include"lexer.hpp"
#include<iostream>
#include<fstream>

void outputToken(std::fstream &f, lex::Token &token);
std::string toHTML(const std::string &text);

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << argv[0] << " source_file\n";
        exit(0);
    }
    
    std::fstream file, ofile;
    file.open(argv[1], std::ios::in);
    
    if(!file.is_open()) {
        std::cerr << "Error could not open file: " << argv[1] << "\n";
        exit(0);
    }
    
    std::string output_filename=argv[1];
    output_filename += ".html";
    
    ofile.open(output_filename, std::ios::out);
    if(!ofile.is_open()) {
        std::cerr << "Could not open output file: " << output_filename << "\n";
        exit(0);
    }
    
    lex::Scanner scan(file);

    ofile << "<html><head><title>" << argv[1] << "</title></head>";
    ofile << "<body>";
    
    ofile << "<table border=\"2\" cellpadding=\"4\"><tr style=\"background-color: rgb(150, 150, 150);\"><td>Index</td><td><b>Token</b></td><td><b>Type</b></td><td><b>Line Number</b></td></tr>";
    
    try {
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            outputToken(ofile, token);
            std::cout << token << "\n";
        }
    } catch(lex::Scanner_EOF) {
        
    } catch(lex::Scanner_Error) {
        std::cerr << "A error has occured.\n";
    }
    
    ofile << "</table></body></html>";
    
    file.close();
    ofile.close();
    
    return 0;
}

void outputToken(std::fstream &out, lex::Token &t) {

    static unsigned int counter = 0;

    if(t.isKeyword() && (t.getTokenType() != lex::TOKEN_STRING && t.getTokenType() != lex::TOKEN_SINGLE)) {
    out << "<tr><td>" << ++counter << "</td><td><b>" << toHTML(t.getToken()) << "</b></td><td>Keyword</td><td>" << t.line << "</td></tr>";
        
    } else {
     out << "<tr><td>" << ++counter << "</td><td>" << toHTML(t.getToken()) << "</td><td>" << t.getType() << "</td><td>" << t.line << "</td></tr>";
    }
}

std::string toHTML(const std::string &text) {
    std::string temp;
    for(unsigned int i = 0; i < text.length(); ++i) {
        switch(text[i]) {
                case '<':
                temp += "&lt;";
                break;
                case '>':
                temp += "&gt;";
                break;
            default:
                temp += text[i];
                break;
        }
    }
    return temp;
}