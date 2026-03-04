#include<iostream>

int main(void) {
	enum Value { one=1, two, three };
	enum class StrongValue { s_one, s_two, s_three };
	StrongValue sv = StrongValue::s_one;
	Value v = one;
	int x = v;
	// error line below wont compile.
	//int y = StrongValue::s_three;
    std::cout << "Value is: " << x << "\n";
    sv = StrongValue::s_two;
	std::cout << "Strong value set to enum index: " << static_cast<int>(sv) << "\n";
	return 0;
}
