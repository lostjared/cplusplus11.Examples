#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<sstream>

std::string urldecode(std::string text);

int main(int argc, char **argv) {
    std::cout << "Content-type: text/html\n\n";
    std::cout << "hello world\n";
    std::string txt="";
    char *data = getenv("QUERY_STRING");
    ///std::cout << data << "\n";
    std::cout << urldecode(data) << "\n";
    
    return 0;
}

std::string urldecode(std::string text) {
    std::ostringstream stream;
    for(unsigned int i = 0; i < text.length(); ++i) {
        if(text[i] == '+') {
            stream << " ";
            continue;
        }
        if(text[i] == '%') {
            if(i+2 < text.length()) {
                ++i;
                std::string test;
                test += text[i];
                ++i;
                test += text[i];
                int char_value;
                sscanf(test.c_str(), "%x", &char_value);
                stream << (char)char_value;
                continue;
            }
        }
        stream << text[i];
    }
    return stream.str();
}
