#include "SDL.h"
#include<iostream>


int main(int argc, char **argv) {
   
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initalizing SDL: " << SDL_GetError() << "\n";
        exit(-1);
    }
    
    SDL_Surface *surf = SDL_SetVideoMode(640, 480, 0, 0);
    SDL_Event e;
    bool active = true;
    while(active == true) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    break;
            }
        }
        SDL_Flip(surf);
    }
    
    SDL_Quit();
    return 0;
}