/*
  A Simple Whiteboard with Boost Asio and SDL 1.2
  1 Person draws in black and the other draws in Red
  You can see what they draw and they can see what you draw
  written by Jared Bruni
  http://lostsidedead.com
 
 How to use:
 
 
 To Listen run with:
 
 ./whiteboard port
 
 To connect run with
 
 ./whiteboard ip port
 
 be sure to forward the port if your behind a router (which you most likely are)
 see your routers control panel to do this.
 
 
 Also be sure to set the path to boost in the Makefile
 

*/

#include<iostream>
#include<sstream>
#include<string>
#include<thread>
#include "boost/asio.hpp"
#include "SDL.h"
#define WIDTH 1280
#define HEIGHT 720

using boost::asio::ip::tcp;

class WhiteBoard {
    
public:
    class Pixel {
    public:
        unsigned char rgb[3];
    };
    WhiteBoard() {
        clear();
    }
    void clear() {
        for(unsigned int i = 0; i < WIDTH; ++i) {
            for(unsigned int z = 0; z < HEIGHT; ++z) {
                pixels[i][z].rgb[0] = 255;
                pixels[i][z].rgb[1] = 255;
                pixels[i][z].rgb[2] = 255;
            }
        }
    }
    void setPixelsFromString(std::string text) {
        std::istringstream stream(text);
        while(!stream.eof()) {
            unsigned int x, y, r, g, b;
            stream >> x >> y >> r >> g >> b;
            for(int i = x; i < x+12; ++i) {
                for(int z = y; z < y+12; ++z) {
                    setPixelToColor(i,z,(unsigned char)r,(unsigned char)g, (unsigned char)b);
                }
            }
        }
    }
    void setPixelToColor(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        if ( x > 0 && x < WIDTH && y > 0 && y < HEIGHT) {
            pixels[x][y].rgb[0] = r;
            pixels[x][y].rgb[1] = g;
            pixels[x][y].rgb[2] = b;
        }
    }
    void copyPixelsToSurface(SDL_Surface *surface) {
        SDL_LockSurface(surface);
        unsigned int *buffer = (unsigned int *)surface->pixels;
        for(unsigned int i = 0; i < WIDTH; ++i) {
            for(unsigned int z = 0; z < HEIGHT; ++z) {
                buffer[i+z*surface->w] = SDL_MapRGB(surface->format, pixels[i][z].rgb[0], pixels[i][z].rgb[1], pixels[i][z].rgb[2]);
            }
        }
        SDL_UnlockSurface(surface);
    }
    Pixel pixels[WIDTH][HEIGHT];
};

SDL_Surface *initSDL(int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: "<< SDL_GetError() << "\n";
        exit(-1);
    }
    
    SDL_Surface *surf = SDL_SetVideoMode(width, height, 0, 0);
    return surf;
}

WhiteBoard board;
bool active = true;

void readSocket(tcp::socket *socket) {
    try {
        while(active == true) {
            unsigned int file_size = 0;
            boost::system::error_code ie;
            boost::asio::read(*socket, boost::asio::buffer(&file_size, sizeof(file_size)));
            
            if(file_size == 0xFFFF) {
                std::cerr << "Exiting..\n";
                exit(0);
            }
            std::string total_str = "";
            size_t file_count = 0;
            std::cout << "Read: " << file_size << " bytes.\n";
            while(file_count < file_size) {
                
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                boost::system::error_code ecode;
                size_t buffer_size = socket->read_some(boost::asio::buffer(buffer, 1024), ecode);
                if(ecode == boost::asio::error::eof)
                    break;
                else if(ecode) {
                    std::cerr << "Program exiting..\n";
                    exit(0);
                }
                total_str += buffer;
                file_count += buffer_size;
            }
            std::cout << "Success Read: " << file_count << " bytes.\n";
            board.setPixelsFromString(total_str);
        }
    } catch(...) {
        std::cout << "Exiting..\n";
        exit(0);
    }
}

int prog_main(int argc, char **argv) {
    boost::asio::io_service io_service;
    tcp::socket *socket;
    SDL_Color blackColor = { 0, 0, 0 };
    if(argc == 2) {
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), atoi(argv[1])));
        socket = new tcp::socket(io_service);
        std::cout << "Whiteboard startup\n";
        std::cout << "Listening on port: " << argv[1] << "\n";
        acceptor.accept(*socket);
        std::cout << "Connected.\n";
    } else if(argc == 3) {
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        socket = new tcp::socket(io_service);
        boost::asio::connect(*socket, endpoint_iterator);
        std::cout << "Connected.\n";
        blackColor.r = 255;
        
    } else {
        std::cerr << "Error invalid operands.\n";
        exit(-1);
    }
    SDL_Surface *surface = initSDL(1280, 720);
    SDL_Event e;
    std::ostringstream stream;
    std::thread back_thread(readSocket, socket);
    back_thread.detach();
    while(active == true) {
        
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    break;
                case SDL_MOUSEMOTION:
                    if(e.motion.state & SDL_BUTTON(1)) {
                        SDL_Color pixelColor = blackColor;
                        for(int x = e.motion.x; x < e.motion.x+12; ++x) {
                            for(int y = e.motion.y; y < e.motion.y+12; ++y) {
                                board.setPixelToColor(x, y, pixelColor.r, pixelColor.g, pixelColor.b);
                            }
                        }
                        stream << e.motion.x << " " << e.motion.y << " " << int(pixelColor.r) << " " << int(pixelColor.g) << " " << int(pixelColor.b) << " ";
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    // send string
                    unsigned int file_size = stream.str().length();
                    boost::system::error_code ie;
                    boost::asio::write(*socket, boost::asio::buffer(&file_size, sizeof(file_size)), ie);
                    boost::asio::write(*socket, boost::asio::buffer(stream.str()));
                    stream.str("");
                    break;
            }
        }
        SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, 255, 255, 255));
        // draw
        board.copyPixelsToSurface(surface);
        SDL_Flip(surface);
    }
    unsigned int file_size = 0xFFFF;
    boost::system::error_code ie;
    boost::asio::write(*socket, boost::asio::buffer(&file_size, sizeof(file_size)), ie);
    delete socket;
    SDL_Quit();
    return 0;
}

int main(int argc, char **argv) {
    try {
        prog_main(argc, argv);
        
    } catch(...) {
        std::cerr << "Exiting.\n";
    }
    return 0;
}


