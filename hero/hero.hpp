#ifndef HERO_H__
#define HERO_H__


/* the Hero object would exist inside of another object */


#include<iostream>
#include<string>
#include<array>
#include<sstream>

namespace game {
    
    // the Tile Matrix
    
    template<typename T, int w, int h>
    class Tiles {
    protected:
        std::array<std::array<T, h>, w> tile_matrix;
     public:
        Tiles() { loadTiles("tiles.txt"); }
        
        T operator()(int x, int y) {
            return tileAt(x,y);
        }
        T tileAt(int x, int y) {
            return tile_matrix[x][y];
        }
        // load tile matrix
        void loadTiles(std::string fileName) {
            for(int x = 0; x < w; ++x) {
                for(int y = 0; y < h; ++y)
                    tile_matrix[x][y] = 1+rand()%255;
            }
        }
    };
    
    class Position {
    protected:
        Position() = default;
        Position(int cx, int cy, int cw, int ch) : x{cx}, y{cy}, w{cw}, h{ch}, cur_frame{0} {}
        int x,y,w,h;
        int cur_frame;
    };
    
    const int width = 640;
    const int height = 480;
    
    Tiles<int, width, height> matrix;
    
    enum {DIRECTION_LEFT=0, DIRECTION_RIGHT, DIRECTION_UP, DIRECTION_DOWN};
    
    class Hero : protected Position {
    public:
        Hero();
        Hero(int x, int y, int w, int h) : Position(x,y,w,h) , speed{1}, direction{DIRECTION_RIGHT} {}
        Hero(int x, int y) : Position(x,y,0,0), speed{1}, direction{DIRECTION_RIGHT} {}
        void move(int dir) {
            switch(dir) {
                case DIRECTION_LEFT:
                    if(x > 0 && matrix.tileAt(x-1, y) >= 1) x -= speed;
                    break;
                case DIRECTION_RIGHT:
                    if(x+1 < width && matrix.tileAt(x+1,y) >= 1)
                        x += speed;
                    break;
                case DIRECTION_UP:
                    if(y > 0 && matrix.tileAt(x,y-1) >= 1) y -= speed;
                    break;
                case DIRECTION_DOWN:
                    if(y+1 < height && matrix.tileAt(x,y+1) >= 1)
                    y += speed;
                    break;
            }
        }
        
        std::string toString() {
            std::ostringstream stream;
            stream << "Hero is at: " << x << ", " << y << ", " << w << ", " << h << "\n";
            stream << "Hero speed: " << speed << "\n";
            return stream.str();
        }
        
    protected:
        int speed, direction;
    };
    
}






#endif
