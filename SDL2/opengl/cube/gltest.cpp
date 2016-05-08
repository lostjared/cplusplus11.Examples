/*
 SDL2 OpenGL Example
 sets up a window and draws a cube.
 using a vertex shader and fragment shader.
 
 - written by Jared Bruni
 adapated from the book "OpenGL Superbible 6th Edition"
 
*/

#include<GL/glew.h>
#include"SDL.h"
#include<iostream>
#include<string>
#include<fstream>
#include "vmath.h"

using namespace vmath;


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

vmath::mat4 proj_matrix, mv_matrix;
GLuint proj_location, mv_location;
float aspect;


void init() {
    
    try {
        if(LoadShader("v.vert", "f.frag") == true) {
            glUseProgram(prog);
        }
    } catch(FileReadError) {
        std::cerr << "Could not open file for shader. Exiting..\n";
        exit(-1);
    }
    
    
    GLfloat vertex_positions[] = { -1.0f, -1.0f, 1.0f, // front face
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        
        -1.0f, -1.0f, -1.0f, // left side
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        
        -1.0f, 1.0f, -1.0f, // top
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        
        -1.0f, -1.0f, -1.0f, // bottom
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        
        1.0f, -1.0f, -1.0f, // right
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        
        -1.0f, -1.0f, -1.0f, // back face
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        
	};
 
    
    GLuint vao;
    GLuint buffer;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    

    proj_location = glGetUniformLocation(prog, "proj_matrix");
    mv_location = glGetUniformLocation(prog, "mv_matrix");
    
}

void render() {
    
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
    
    static float z = 1.0f;
    
    z += 1.0f;
    
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
    
    for(int i = 0; i < 5; ++i) {
    
        mv_matrix = vmath::translate(-8.0f+(i*3.0f),0.0f, -16.0f) * vmath::rotate(z, 1.0f, 0.0f, 1.0f);
        glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
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
    aspect = float(src_closest.w) / float(src_closest.h);
    proj_matrix = vmath::perspective(50.0f,aspect,0.1f, 1000.0f);

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
        render();
        SDL_GL_SwapWindow(window);
        
    }
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
