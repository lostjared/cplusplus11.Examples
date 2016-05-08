/*
 SDL2 OpenGL Example
 sets up a window and draws a few triangles
 using a vertex shader and fragment shader.
 
 - written by Jared Bruni
 adapated from the book "OpenGL Programming Guide " 8th Edition
 
*/

#include<GL/glew.h>
#include"SDL.h"
#include<iostream>
#include<string>
#include<fstream>



#define BUFFER_OFFSET(i) ((char *)NULL + (i))
class FileReadError {};


GLint vert, frag, prog;

std::string readFile(std::string f) {
    std::fstream file;
    file.open(f.c_str(), std::ios::in | std::ios::binary);
    if(!file.is_open()) {
        throw FileReadError();
    }
    unsigned long size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *buf = new char [size+1];
    file.read(buf, size);
    buf[size] = 0;
    std::string text = buf;
    delete [] buf;
    file.close();
    return text;
}



bool LoadShader(std::string f_vert, std::string f_frag) {
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    prog = glCreateProgram();
    
    std::string vert_text = readFile(f_vert);
    std::string frag_text = readFile(f_frag);
    
    const char *vs = (const char *)vert_text.c_str();
    const char *fs = (const char *)frag_text.c_str();
    
    glShaderSource(vert, 1, &vs, NULL);
    glShaderSource(frag, 1, &fs, NULL);

    int len = 0;
    glCompileShader(vert);
    GLint result;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
    if(result == GL_TRUE) {
        glAttachShader(prog, vert);
    } else {
        GLchar *str = (GLchar*)malloc(5096);
        glGetShaderInfoLog(vert, 5096, &len, str);
        printf("vertex shader: %s\n", str);
        free(str);
        exit(0); // exit
    }
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
    if(result == GL_TRUE)
        glAttachShader(prog, frag);
    else {
        GLchar *str = (GLchar*)malloc(5096);
        glGetShaderInfoLog(frag, 5096, &len, str);
        printf("fragment: %s\n", str);
        free(str);
        exit(0); // exit
    }
    
    glBindAttribLocation(prog, 0, "a_Vertex");
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS,&result);
    if(result == GL_TRUE) {
        return true;
    }
    GLchar *str = (GLchar*)malloc(5096);
    glGetProgramInfoLog(prog, 5096, &len, str);
    printf("Program %s\n", str);
    free(str);
    exit(0);// exit
    return false;
}

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[1];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

void init() {
    glGenVertexArrays(1, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    
    GLfloat  vertices[NumVertices][2] = {
        { -0.90, -0.90 },  // Triangle 1
        {  0.85, -0.90 },
        { -0.90,  0.85 },
        {  0.90, -0.85 },  // Triangle 2
        {  0.90,  0.90 },
        { -0.85,  0.90 }
    };
    
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    try {
        if(LoadShader("v.vert", "f.frag") == true) {
            glUseProgram(prog);
        }
    } catch(FileReadError) {
        std::cerr << "Could not open file for shader. Exiting..\n";
        exit(-1);
    }
    
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void render() {
    // draw something
    
    glBindVertexArrayAPPLE(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    
    glFlush();
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
    
    SDL_Window *window = SDL_CreateWindow("OpenGL SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, src_closest.w, src_closest.h, SDL_WINDOW_OPENGL);
    
    if(SDL_SetWindowDisplayMode(window, &src_closest)) {
        std::cerr << "Could Not set display mode.\n";
        SDL_Quit();
        return -1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    
    if(glewInit()) {
        std::cerr << "Error initalizing GLEW.\n";
        exit(-1);
    }
    
    std::cout <<"GL Version: "<< glGetString(GL_VERSION) << "\n";

    init();
    glViewport(0, 0, src_closest.w, src_closest.h);
 
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
        glClear(GL_COLOR_BUFFER_BIT);
        render();
        SDL_GL_SwapWindow(window);
        
    }
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
