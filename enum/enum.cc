#include<iostream>

int main(int argc, char **argv) {
	enum Value { one=1, two, three };
	enum class StrongValue { s_one, s_two, s_three };
	StrongValue sv = StrongValue::s_one;
	Value v = one;
	int x = v;
	// error line below wont compile.
	//int y = StrongValue::s_three;
    std::cout << "Value is: " << x << "\n";
    sv = StrongValue::s_two;
	return 0;
}
