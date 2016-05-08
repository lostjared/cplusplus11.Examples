#include<iostream>
#include<string>

class ObjectType {
	std::string text;
public:
	ObjectType() = default;
	// disallow copying
	ObjectType(const ObjectType &t) = delete;
	void operator=(const ObjectType &t) = delete;
	void operator=(std::string text);
	// print text
	void say(std::string text);
};

void ObjectType::say(std::string text) {
	std::cout << text << "\n";
	this->text = text;
}

void ObjectType::operator=(std::string text) {
	this->text = text;
}


template<typename Type1, typename Type2>
auto Proc(Type1 type1, Type2 type2) -> decltype(type1*type2) {
	return (type1*type2);
}


int main(int argc, char **argv) {

	
	ObjectType otype, ctype;

	otype.say("Hello World\n");
	
	// copying not allowed 
	// otype = ctype;
	
	// ok
	otype = "test";
	
	int value = Proc<int, int>(10, 10);
	std::cout << " value = " << value << "\n";
	double dvalue = Proc<double, double>(10.5, 10.5);
	std::cout << " double value = " << dvalue << "\n";
	
	
	return 0;
}