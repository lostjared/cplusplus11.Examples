/* written by Jared Bruni
   http://lostsidedead.com
*/


#include"SDL.h"
#include<iostream>


void rand_pixels(SDL_Texture *tex, SDL_Surface *surface) {
    SDL_LockTexture(tex, 0, &surface->pixels, &surface->pitch);
    for(unsigned int i = 0; i < surface->w; ++i) {
        for(unsigned int z = 0; z < surface->h; ++z) {
            unsigned int *ptr = (unsigned int *)surface->pixels+ (i+z*surface->w);
            *ptr = SDL_MapRGB(surface->format, rand()%255, rand()%255, rand()%255);
        }
    }
    SDL_UnlockTexture(tex);
}

int main(int argc, char **argv) {
    const int width=640, height=480;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << SDL_GetError() << "\n";
    }
    
    SDL_Window *window = SDL_CreateWindow("Hello World Random Pixels", 0, 0, width, height, SDL_WINDOW_SHOWN);
    
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(ren == 0) {
        std::cout << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }
    
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(NULL, width, height, 32, 0, 0x00FF0000, 0x0000FF00,0x000000FF,0xFF000000);
    
    bool active = true;
    SDL_Event e;
    
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    break;
                case SDL_QUIT:
                    active = false;
                    break;
            }
        }
        
        SDL_RenderClear(ren);
        rand_pixels(tex, surface);
        SDL_RenderCopy(ren, tex, 0, 0);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_Quit();
    return 0;
}
