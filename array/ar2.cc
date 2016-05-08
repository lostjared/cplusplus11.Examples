/*
 
 
 C++11 uses std::array
 
 written by Jared Bruni
 http://lostsidedead.com
*/




#include<iostream>
#include<iomanip>
#include<array>

namespace mx {

    
    template<typename T, int cx, int cy>
    class Grid {
    public:
        Grid();
        T &operator()(int x, int y) { return grid[x][y]; }
        void fill(const T &t);
        T accumulate();
        T average();
        
        friend std::ostream &operator<<(std::ostream &out, Grid<T,cx,cy> &g) {
            for(int i = 0; i < cx; ++i) {
                for(int z = 0; z < cy; ++z) {
                    out << std::setw(4) << g(i,z) << " ";
                }
                out << "\n";
            }
            return out;
        }
        
    protected:
        std::array<std::array<T, cx>, cy> grid;
        
    };


    template<typename T, int cx, int cy>
    Grid<T,cx,cy>::Grid() {
        std::cout << "Grid initialized to: " << cx << " " << cy << "\n";
    }

    template<typename T, int cx, int cy>
    void Grid<T,cx,cy>::fill(const T &t) {
        for(int x = 0; x < cx; ++x) {
            for(int y = 0; y < cy; ++y) {
                grid[x][y] = t;
            }
        }
    }

    template<typename T, int cx, int cy>
    T Grid<T,cx,cy>::accumulate() {
      
        T total{};
        for(int x = 0; x < cx; ++x) {
            for(int y = 0; y < cy; ++y)
                total += grid[x][y];
        }
        return total;
    }

    template<typename T, int cx, int cy>
    T Grid<T,cx,cy>::average() {
        return accumulate()/(cx*cy);
    }

}
int main(int argc, char **argv) {
    using namespace mx;
    try {
        // 4 x 4 of type int
        Grid<int, 4, 4> grid;
        for(int x = 0; x < 4; ++x) {
            for(int y = 0; y < 4; ++y) {
                grid(x,y) = std::rand()%100;
            }
        }
        int total=grid.accumulate();
        int average = grid.average();
        std::cout << grid << "\n";
        std::cout << "Total of all elements: " << std::setw(4) << total << "\n";
        std::cout << "Average of elements: "<< std::setw(4) << average << "\n";
        std::cout << "Enter x y of 4,4 vector: ";
        int i,z;
        std::cin >> i >> z;
        if(i >= 0 && z >= 0 && i < 4 && z < 4) {
            std::cout << "Element at: " << i << "," << z << " = " << grid(i,z) << "\n";
        } else {
            std::cerr << "Invalid enter number 0-4\n";
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Error.\n";
    }
    
    return 0;
}