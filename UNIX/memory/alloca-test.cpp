#include<iostream>
#include<alloca.h>


void averageNumbers(int *values, int s);
void calcAverage();

int main(int argc, char **argv) {
    calcAverage();
    return 0;
}

void averageNumbers(int *values, int s) {
    std::cout << "Enter values: ";
    int total = 0;
    for(int i = 0; i < s; ++i) {
        std::cin >> values[i];
        total += values[i];
    }
    total /= s;
    std::cout << "Average is: " << total << "\n";
}

void calcAverage() {
    
    std::cout << "How many numbers? ";
    int num_values = 0;
    std::cin >> num_values;
    int *av = (int*)alloca(sizeof(int)*num_values); // allocate on the stack
    if(av == 0) {
        std::cerr << "Error allocating numbers..\n";
        exit(0);
    }
    averageNumbers(av, num_values);
}
