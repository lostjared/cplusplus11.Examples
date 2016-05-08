//
//  Created by Jared Bruni on 7/9/13.
//

#include <iostream>

constexpr int calcNum(int num) {
    return (num/2)/16;
}

constexpr int Calc = calcNum(400);
int arr_temp[Calc]; // note constexpr


//another

template<typename T, int Num>
class ArrTile {
public:
    T type[calcNum(Num)]; // note constexpr
    
    T &operator[](unsigned int i) { return type[i]; }
};


int main(int argc, char **argv)
{
    ArrTile<int, 400> arrTile;
    arrTile[0] = 0;
    
    return 0;
}

