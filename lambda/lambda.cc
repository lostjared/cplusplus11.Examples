/* 
 
 Messing around with C++11 
 I Love C++
  
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class O {
	std::vector<char> vec;
public:
	O() = default;
	/* disallow copying */
	O(const O& o) = delete;
	void operator=(const O& o) = delete;
	/* method to call lambda function */
	template<typename Function>
	void procList(Function func);
	void push(char c);
	void push(std::string text);
    template<typename Function>
	void sort(Function f);
	char &operator[](int pos) noexcept;
	
};


template<typename Function>
void O::procList(Function func) {
	for(auto i = vec.begin(); i != vec.end(); ++i) {
		func(*i);
	}
}

void O::push(char c) {
	vec.push_back(c);
}

void O::push(std::string text) {
	for(auto i = text.begin(); i != text.end(); ++i)
		push(*i);
}

template<typename F>
void O::sort(F func) {
	std::sort(vec.begin(), vec.end(), func);
}

char &O::operator[](int pos) noexcept {
	return vec[pos];
}

int main(int argc, char **argv) {
	std::cout << "Enter some text: ";
	std::string str = "";
	std::getline(std::cin, str);
	O o;
	o.push(str);
	int count = 0;
	/* use local variable, count (passed by reference) */
	o.procList( [&count](char ch) {
		std::cout << "Character: " << ch << "\n";
		++count;
	});
	std::cout << "There are: " << count << " Characters entered\n";
	o.sort([&](int x, int y) { return x<y; });
	int index = 0;
	/* grab all variables in scope pass by reference */
	o.procList( [&](char ch) {
		std::cout << index << ": " << ch << "\n";
		++index;
	});
	return 0;
}