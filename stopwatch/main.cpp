#include<iostream>
#include<string>
#include"stopwatch.hpp"


int main() {
	
	StopWatch<SystemClock> value_wait("Outter Loop");
	for(unsigned int i = 0; i < 100; ++i) {
		for(unsigned int i = 0; i < 100; ++i) {
			StopWatch<HighResolutionClock> inner_loop("Inner Loop");
			for(unsigned z = 0; z < 10000; ++z) { }
		}
	}
	
	return 0;
}