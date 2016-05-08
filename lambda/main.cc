#include<iostream>
#include<vector>

int main(int argc, char **argv) {

	std::vector<int> vec = { 2, 6, 0, 5, 7 };
	
	int findLargest = [](std::vector<int> &v) {
		int large=0;
		for(auto &i : v) {
			if(i > large) large = i;
		}
		return large;
	} (vec);
	
	std::cout << findLargest << "\n";
	
	return 0;
}

