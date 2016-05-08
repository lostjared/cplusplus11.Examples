#ifndef IOMAX_H_
#define IOMAX_H_

#include<iostream>
#include<algorithm>

// read integer from stream
int getInteger(std::istream &istr) {
	std::string val;
	std::getline(istr, val);
	return atoi(val.c_str());
}
// read string (line) from stream
std::string getString(std::istream &istr) {
	std::string val;
	std::getline(istr, val);
	return val;
}

#endif
