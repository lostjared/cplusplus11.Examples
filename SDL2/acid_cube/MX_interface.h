#ifndef __HEADER__H__
#define __HEADER__H__


#include<GL/glew.h>

namespace MX_i {
    extern int FPS;
    extern float dt;
    void Init(int *argc, char **argv, int w, int h);
    void SetCallbacks(void (*update)(), void (*idle)(), void (*resize)(int w, int h));
    void Loop();
    void Quit();
    void SwapBuffers();
    void Redisplay();
    void CreateTimer(unsigned int (*timer)(unsigned int i), int timeout);
    GLubyte *LoadBMP(const char *src, int *w, int *h);
    unsigned int GetTicks();
    enum Buttons { B_UP=0, B_DOWN, B_LEFT, B_RIGHT, B_1,B_2, B_3, B_4, B_5, B_6};
    bool PollController(enum Buttons b);
}

#endif


