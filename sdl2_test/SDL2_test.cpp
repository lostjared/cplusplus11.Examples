#include<iostream>
#include"SDL.h"
#include"SDL_opengl.h"

void render() {
    // draw something
}

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initailizing..\n";
        return -1;
    }
    SDL_Event e;
    SDL_DisplayMode src, src_closest;
    
    src.w = 640;
    src.h = 480;
    src.format = 0;
    src.refresh_rate = 0;
    src.driverdata = 0;
    
    if(SDL_GetClosestDisplayMode(0, &src, &src_closest) == NULL) {
        std::cerr << "No acceptable display mode.\n";
        SDL_Quit();
        return -1;
    }
    
    SDL_Window *window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, src_closest.w, src_closest.h, SDL_WINDOW_OPENGL);
    
    if(SDL_SetWindowDisplayMode(window, &src_closest)) {
        std::cerr << "Could Not set display mode.\n";
        SDL_Quit();
        return -1;
    }
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-320,320,240,-240,0,1);
    glClearColor(1,1,1,1);
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
            }
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        render();
        SDL_GL_SwapWindow(window);
        
    }
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
