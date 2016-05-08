/* written by Jared Bruni
 * http://lostsidedead.com
 */

#include"tile.hpp"
#include<iostream>
#include<iomanip>
#include<chrono>

class Graphic {
public:
    int graphic = 0;
};


constexpr int videoSize_W=640/4, videoSize_H=480/4;

std::ostream &operator<<(std::ostream &out, Graphic &g) {
    out << "Graphic index: " << g.graphic << " ";
    return out;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, tilemx::Tile<T> &t) {
    out << std::setw(4) << t.x << ", " << std::setw(4) << t.y << ", " << std::setw(4) << t.w << ", " << std::setw(4) << t.h << "{ " << t.value() << " } \n";
    return out;
}

template<typename T, int W, int H>
std::ostream &operator<<(std::ostream &out,tilemx::TileMatrix<T,W,H> &t) {
    for(int i = 0; i < W; ++i)
        for(int z = 0; z < H; ++z)
            out << t.tileAt(i, z) << "\n";
    return out;
}

int main(int argc, char **argv) {
    using namespace std::chrono;
    try {
        tilemx::TileMatrix<Graphic, videoSize_W, videoSize_H> matrix;
        // fill matrix
        // how long does the loop take?
        high_resolution_clock::time_point start = high_resolution_clock::now();
        for(tilemx::value_int x = 0; x < videoSize_W; ++x) {
            for(tilemx::value_int y = 0; y < videoSize_H; ++y) {
                tilemx::Tile<Graphic> &g = matrix.tileAt(x, y);
                g.value().graphic = rand()%255;
                g.x = x;
                g.y = y;
                g.w = 25;
                g.h = 25;
            }
        }
        
        high_resolution_clock::time_point stop = high_resolution_clock::now();
        std::cout << "Loop took: " << duration_cast<nanoseconds>(stop-start).count() << " nano seconds\n";
        matrix.applyFunction([](tilemx::value_int x, tilemx::value_int y, tilemx::Tile<Graphic> &t) { t.value().graphic++; } );
        std::cout << matrix << "\n";
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "ack error.\n";
    }

	return 0;
}
