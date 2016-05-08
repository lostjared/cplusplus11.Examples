#ifndef __REPLACE_H__
#define __REPLACE_H__

#include<iostream>
#include<string>

class NotFound {};


std::string replaceString(const std::string &text, const std::string &rep_source, const std::string &rep_what) {
    std::string temp = text;
    int pos = temp.find(rep_source);
    if(pos == -1) throw NotFound();
    while( pos != -1 ) {
        std::string left_value=temp.substr(0, pos);
        std::string right_value = temp.substr(pos + rep_source.length(),temp.length());
        temp = left_value+rep_what+right_value;
        pos = temp.find(rep_source);
    }
    return temp;
}











#endif
