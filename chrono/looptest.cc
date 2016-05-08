/*

    written by Jared Bruni
    http://lostsidedead.com

*/

#include<iostream>
#include<chrono>

namespace arrTest {
    
    using namespace std;
    
    template<typename T, int sizeX, int sizeY>
    class MultiArray {
    public:
        T arr[sizeX][sizeY] = { {T()} };
        void XFirst();
        void YFirst();
    };

    template<typename T, int sizeX, int sizeY>
    void MultiArray<T,sizeX, sizeY>::XFirst() {
        auto p1 = chrono::high_resolution_clock::now();
        for(int x = 0; x < sizeX; ++x) {
            for(int y = 0; y < sizeY; ++y) {
                arr[x][y] = x*y;
            }
        }
        auto p2 = chrono::high_resolution_clock::now();
        std::cout << "X first Loop took exactly: " << chrono::duration_cast<chrono::nanoseconds>(p2-p1).count() << " nanoseconds. \n";
    }

    template<typename T,int sizeX, int sizeY>
    void MultiArray<T, sizeX, sizeY>::YFirst() {
        auto p1 = chrono::high_resolution_clock::now();
        for(int y = 0; y < sizeY; ++y) {
            for(int x = 0; x < sizeX; ++x) {
                arr[x][y] = x*y;
            }
        }
        auto p2 = chrono::high_resolution_clock::now();
        std::cout << "Y first Loop took exactly: " << chrono::duration_cast<chrono::nanoseconds>(p2-p1).count() << " nanoseconds. \n";
    }
}

int main(int argc, char **argv) {
    arrTest::MultiArray<int, 1000, 1000> arr;
    
    arr.XFirst();
    arr.YFirst();
    return 0;
}
