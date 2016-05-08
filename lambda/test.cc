

#include<iostream>
#include<map>
#include<string>

class Object {

public:	
	Object() {}

	typedef void (*Function)();
	
	std::map<std::string, Function> object_functions;
	
	Function &operator[](std::string func_name) {
		return object_functions[func_name];
	}
	
	void (*update_func)();
	void (*keyfunc)(int key);
};


int main(int argc, char **argv) {

	Object obj;
	obj.update_func = [](){
		std::cout << "UPDATE\n";
	};
	
	obj.keyfunc = [](int key){
		if(key == 13) std::cout << "yes..\n";
	};
	
	obj.keyfunc(13);
	obj.update_func();
	
	obj["func"] = []() { std::cout << "Hello World\n"; };
	obj["func"]();
	int input=0;
    std::cin >> input;
	([](int x){ for(int i = x; i < 4; ++i) std::cout << "counter: " << i << std::endl; })(input);
	
	
	return 0;
}