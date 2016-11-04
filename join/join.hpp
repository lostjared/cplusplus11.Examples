#ifndef __JOIN_H__
#define __JOIN_H__
#include<string>
#include<iterator>
#include<sstream>

template<typename T>
std::string join(const T &type, std::string sep=",") {
    std::ostringstream stream;
    for(auto i = std::begin(type); i != std::end(type); ++i) {
        if(i == std::end(type)-1)
            stream << *i;
        else
            stream << *i << sep;
    }
    return stream.str();
}

#endif
