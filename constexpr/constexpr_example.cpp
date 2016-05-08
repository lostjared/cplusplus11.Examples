#include<iostream>

constexpr int bysize(const int size) {
    return size/16; // can only be on liner in C++11
}

constexpr int w = 640;
constexpr int h = 480;


template<typename T, int w, int h>
class Tile {
public:
    
    Tile() {
        init();
    }
    
    T tiles[bysize(w)][bysize(h)];
    
    void init() {
        
        for(unsigned int i = 0; i < bysize(w); ++i) {
            for(unsigned int z = 0; z < bysize(h); ++z) {
                tiles[i][z] = T();
            }
        }
    }
    
    void setTile(const int x, const int y, const T value) {
        tiles[x][y] = value;
    }
    
    
    const T& operator()(const int x, const int y) {
        return tiles[x][y];
    }
};


int main(int argc, char **argv) {
    
    Tile<int, w, h> tiles;
    
    tiles.setTile(39, 29, 256);
    
    for(unsigned int i = 0; i < bysize(w); ++i) {
        for(unsigned int z = 0; z < bysize(h); ++z) {
            std::cout << "Tile at (" << i << ", " << z << "): " << tiles(i, z) << "\n";
        }
    };
    
    return 0;
}
