// will draw a random tilemap of 8x8 pixels at resolution of 640x480
// with SDL 1.2
#include"SDL.h"
#include"../tile.hpp"
#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<ctime>

constexpr int tileSize = 8;
constexpr int videoW = 640/tileSize, videoH = 480/tileSize;
constexpr int screens = 3;
constexpr int videoSize_W=videoW*screens, videoSize_H=videoH*screens;

class Graphic {
public:
    int graphic = 0;
};

using VideoMatrix = tilemx::TileMatrix<Graphic, videoSize_W, videoSize_H>;
Uint32 colors[32];

void fillMatrix(SDL_Surface *,VideoMatrix &);
void render(SDL_Surface *, VideoMatrix &);


std::ostream &operator<<(std::ostream &out, Graphic &g) {
    out << " Graphic index: " << std::setw(4) << g.graphic << " ";
    return out;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, tilemx::Tile<T> &t) {
    out << std::setw(4) << t.x << ", " << std::setw(4) << t.y << ", " << std::setw(4) << t.w << ", " << std::setw(4) << t.h << " { " << t.value() << " } \n";
    return out;
}

template<typename T, int W, int H>
std::ostream &operator<<(std::ostream &out,tilemx::TileMatrix<T,W,H> &t) {
    for(int i = 0; i < W; ++i)
        for(int z = 0; z < H; ++z)
            out << t.tileAt(i, z) << "\n";
    return out;
}

Uint32 timerCallback(Uint32 interval, void *param) {
    VideoMatrix *matrix = static_cast<VideoMatrix *>(param);
    Uint8 *keys = SDL_GetKeyState(0);
    if(keys[SDLK_LEFT]) {
        matrix->scroll_left();
    } else if(keys[SDLK_RIGHT]) {
        matrix->scroll_right(videoW);
    }
    if(keys[SDLK_UP]) {
        matrix->scroll_up();
    } else if(keys[SDLK_DOWN]) {
        matrix->scroll_down(videoH);
    }
    return interval;
}

int main(int argc, char **argv) {
    using namespace tilemx;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) return -1;
    std::cout << "Initialized. Press Escape to Exit.\n";
    SDL_Surface *front;
    front = SDL_SetVideoMode(640, 480, 0, 0);
    if(!front) {
        std::cerr << "Error could not set video mode.\n";
        SDL_Quit();
        return -1;
    }
    TileMatrix<Graphic, videoSize_W, videoSize_H> map;
    fillMatrix(front, map);
    SDL_TimerID id = SDL_AddTimer(1, timerCallback,&map);
    SDL_Event e;
    bool active = true;
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                        active = false;
                        break;
                default:
                    break;
            }
        }
        render(front, map);
        SDL_Flip(front);
    }
    std::cout << "The map was: " << map << "\n";
    std::cout << "Exited.\n";
    SDL_RemoveTimer(id);
    SDL_Quit();
    return 0;
}

void render(SDL_Surface *surface, VideoMatrix &matrix) {
    for(tilemx::value_int i = 0; i < videoW; ++i) {
        for(tilemx::value_int z = 0; z < videoH; ++z) {
            SDL_Rect rc;
            rc.x = i * tileSize;
            rc.y = z * tileSize;
            rc.w = tileSize;
            rc.h = tileSize;
            tilemx::Tile<Graphic> &g = matrix.tileAt(matrix.offsetX()+i, matrix.offsetY()+z);
            // for now just draw a rect
            SDL_FillRect(surface, &rc, colors[g.value().graphic]);
        }
    }
}

void fillMatrix(SDL_Surface *surface, VideoMatrix &map) {
    map.initCoords(tileSize);
    std::srand(static_cast<unsigned int>(time(0)));
    map.applyFunction([](const tilemx::value_int x, const tilemx::value_int y, tilemx::Tile<Graphic> &g) { g.value().graphic = std::rand()%32; });
    // fill in the colors array with random colors
    for(unsigned int i = 0; i < 32; ++i) {
        colors[i] = SDL_MapRGB(surface->format, std::rand()%255, std::rand()%255, std::rand()%255);
    }
}

