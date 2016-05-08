#ifndef __JOIN_H__
#define __JOIN_H__
#include<string>
#include<iterator>

template<typename T>
std::string join(const T &type, std::string sep=",") {
    std::string str_value;
    for(auto i = std::begin(type); i != std::end(type); ++i) {
        if(i == std::end(type)-1)
            str_value += *i;
        else
            str_value += *i + sep;
    }
    return str_value;
}

#endif
