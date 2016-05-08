
#include<iostream>
#include<string>


class MemberFunctionSyntax {
  
public:
    auto function_name(int x, int y) -> decltype(x) {
        return x+y;
    }
    template<typename T>
    auto function_name(T &t) -> decltype(t) {
        return t+t;
    }
};


// alternate function decl syntax
auto function_def(int x, int y) -> int {
	
	// lambda 
	auto func_def = [](int x, int y) -> int {
		return x+y;
	};
	
	return func_def(x,y);
}

auto main(int argc, char **argv) -> int {
    std::cout << "Hello World\n";
    return 0;
}