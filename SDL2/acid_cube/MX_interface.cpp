#include "MX_interface.h"
#include"SDL.h"
#include<sys/time.h>
#include<iostream>

namespace MX_i {
    
    SDL_Joystick *stick;
    SDL_GLContext glcontext;
    SDL_Window *window;
    SDL_TimerID timer_id;
    bool Buttons[0xFF];
    
    void (*update_cb)();
    void (*idle_cb)();
    void (*resize_cb)(int, int);
    
    size_t total=0;
    
    int view_w, view_h;
    
    void Init(int *argc, char **argv, int w, int h) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
        view_w = w;
        view_h = h;
        SDL_JoystickEventState(SDL_ENABLE);
        stick = SDL_JoystickOpen(0);
    }
    
    void SetCallbacks( void (*update)(), void (*idle)(), void (*resize)(int w, int h)) {
        update_cb = update;
        resize_cb = resize;
        idle_cb = idle;
        
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        
        
        window = SDL_CreateWindow("Acid Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, view_w, view_h, SDL_WINDOW_OPENGL);
        
        glcontext = SDL_GL_CreateContext(window);
        glewExperimental = GL_TRUE;
        glewInit();
        std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
        
        SDL_GL_MakeCurrent(window, glcontext);
        SDL_GL_SetSwapInterval(1);
        resize_cb(view_w, view_h);
        
        // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    
    bool done;
    
    void Loop() {
        
        SDL_Event e;
        
        done = false;
        
        while(!done) {
            
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        done = true;
                        break;
                    case SDL_JOYBUTTONUP:
                        if(e.jbutton.button == 1) Buttons[B_1] = false;
                        break;
                    case SDL_JOYBUTTONDOWN:
                        if(e.jbutton.button == 1) Buttons[B_1] = true;
                        break;
                    case SDL_JOYHATMOTION:
                        
                        if(e.jhat.value & SDL_HAT_UP) { Buttons[B_UP] = true; break; }
                        else Buttons[B_UP] = false;
                        
                        
                        
                        if(e.jhat.value & SDL_HAT_LEFT) { Buttons[B_LEFT] = true; break; }
                        else  Buttons[B_LEFT] = false;
                        
                        if(e.jhat.value & SDL_HAT_RIGHT) { Buttons[B_RIGHT] = true; break; }
                        else Buttons[B_RIGHT] = false;
                        
                        if(e.jhat.value & SDL_HAT_DOWN) { Buttons[B_DOWN] = true; break; }
                        else Buttons[B_DOWN] = false;
                        
                        
                        break;
                    case SDL_JOYAXISMOTION: {
                        
                        int numAxis = SDL_JoystickNumAxes(stick);
                        
                        if(e.jaxis.axis == 3) {
                            if(e.jaxis.value < -3200) {
                                Buttons[B_3] = true;
                            } else Buttons[B_3] = false;
                            
                            if(e.jaxis.value > 3200) {
                                Buttons[B_2] = true;
                            } else Buttons[B_2] = false;
                            
                        } else if(e.jaxis.axis == 2) {
                            if(e.jaxis.value < -3200) {
                                Buttons[B_5] = true;
                            } else Buttons[B_5] = false;
                            
                            if(e.jaxis.value > 3200)
                                Buttons[B_4] = true;
                            else
                                Buttons[B_4] = false;
                        }
                        
                    }
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_ESCAPE) done = true;
                        switch(e.key.keysym.sym) {
                            case SDLK_LEFT:
                                Buttons[B_LEFT] = true;
                                break;
                            case SDLK_RIGHT:
                                Buttons[B_RIGHT] = true;
                                break;
                            case SDLK_UP:
                                Buttons[B_UP] = true;
                                break;
                            case SDLK_DOWN:
                                Buttons[B_DOWN] = true;
                                break;
                                break;
                            case SDLK_a:
                                Buttons[B_1] = true;
                                break;
                            case SDLK_s:
                                Buttons[B_2] = true;
                                break;
                            case SDLK_d:
                                Buttons[B_3] = true;
                                break;
                            case SDLK_z:
                                Buttons[B_4] = true;
                                break;
                            case SDLK_x:
                                Buttons[B_5] = true;
                                break;
                            case SDLK_e:
                                Buttons[B_6] = true;
                                break;
                            default:
                                break;
                                
                        }
                        break;
                    case SDL_KEYUP:
                        switch(e.key.keysym.sym) {
                            case SDLK_LEFT:
                                Buttons[B_LEFT] = false;
                                break;
                            case SDLK_RIGHT:
                                Buttons[B_RIGHT] = false;
                                break;
                            case SDLK_UP:
                                Buttons[B_UP] = false;
                                break;
                            case SDLK_DOWN:
                                Buttons[B_DOWN] = false;
                                break;
                            case SDLK_a:
                                Buttons[B_1] = false;
                                break;
                            case SDLK_s:
                                Buttons[B_2] = false;
                                break;
                            case SDLK_d:
                                Buttons[B_3] = false;
                                break;
                            case SDLK_z:
                                Buttons[B_4] = false;
                                break;
                            case SDLK_x:
                                Buttons[B_5] = false;
                                break;
                            case SDLK_e:
                                Buttons[B_6] = false;
                                break;
                                
                            default:
                                break;
                        }
                        break;
                    case SDL_WINDOWEVENT:
                        switch(e.window.event) {
                            case SDL_WINDOWEVENT_CLOSE:
                                done = true;
                                break;
                        }
                        break;
                        
                }
            }
            idle_cb();
        }
        
        
    }
    
    void Quit() {
        SDL_RemoveTimer(timer_id);
        SDL_JoystickClose(stick);
        SDL_GL_DeleteContext(glcontext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    unsigned int (*timer_cb)(unsigned int t);
    
    Uint32 t_cb(Uint32 t, void *param) {
        return timer_cb(t);
    }
    
    void CreateTimer(unsigned int (*timer)(unsigned int t), int timeout) {
        timer_cb = timer;
        timer_id=SDL_AddTimer(timeout,t_cb,0);
    }
    
    void SwapBuffers() {
        SDL_GL_SwapWindow(window);
    }
    
    void Redisplay() {
        update_cb();
    }
    
    unsigned int GetTicks() {
        return SDL_GetTicks();
    }
    
    bool PollController(enum Buttons b) {
        return Buttons[b];
    }
}
