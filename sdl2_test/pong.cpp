/* written by Jared Bruni
   http://lostsidedead.com
*/


#include"SDL.h"
#include<iostream>
#include<map>


const int width=640, height=480;

class Paddle {
public:
    Paddle() = default;
    int x, y, width, height, scr = 0;
    
    void moveDown() {
        if(y < ::height-100) y += 10;
    }
    void moveUp() {
        if(y > 0) y -= 10;
    }
    
    void score() {
        scr += 5;
    }
};

class Ball {
public:
    Ball() = default;
    int x,y,w,h,dir;
};

class GameBoard {
public:
    GameBoard() {
        player1.x = 40;
        player1.y = (480-100)/2;
        player2.x = 640-30;
        player2.y = (0);
        player1.width = 10;
        player1.height = 100;
        player2.width = 30;
        player2.height = 480;
        ball.x = (640/2)-(10/2);
        ball.y = (480/2)-(10/2);
        ball.w = 10;
        ball.h = 10;
        ball.dir = 4;
    }
    Paddle player1, player2;
    Ball ball;
};

GameBoard game;

void drawFrame(SDL_Renderer *ren, SDL_Texture *paddle, SDL_Texture *ball_tex);
void procGame(Paddle &one, Paddle &two, Ball &ball, int speed);

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << SDL_GetError() << "\n";
    }
    SDL_Window *window = SDL_CreateWindow("Pong Test", 0, 0, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == 0) {
        std::cout << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(NULL, width, height, 32, 0, 0x00FF0000, 0x0000FF00,0x000000FF,0xFF000000);
    SDL_Surface *paddle = SDL_LoadBMP("paddle.bmp");
    SDL_Surface *ball = SDL_LoadBMP("ball.bmp");
    
    SDL_SetColorKey(ball, SDL_TRUE, 0);
    if(!paddle || !ball) {
        std::cerr << "Error could not load bitmap\n";
        SDL_Quit();
        return -1;
    }
    SDL_Texture *paddle_tex = SDL_CreateTextureFromSurface(ren, paddle);
    SDL_FreeSurface(paddle);
    SDL_Texture *ball_tex = SDL_CreateTextureFromSurface(ren, ball);
    
    bool active = true;
    SDL_Event e;
    
    std::map<int, int> keys;
    
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    keys[e.key.keysym.sym] = 1;
                    break;
                case SDL_KEYUP:
                    keys[e.key.keysym.sym] = 0;
                    break;
                case SDL_QUIT:
                    active = false;
                    break;
            }
        }
        

        if(keys[SDLK_UP] == 1) game.player1.moveUp();
        if(keys[SDLK_DOWN] == 1) game.player1.moveDown();
    
        SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, rand()%255, rand()%255, rand()%255));
        SDL_LockTexture(tex, 0, &surface->pixels, &surface->pitch);

        
        
        SDL_UnlockTexture(tex);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, 0, 0);
        drawFrame(ren, paddle_tex, ball_tex);
        procGame(game.player1, game.player2, game.ball, 5);
        SDL_RenderPresent(ren);
        SDL_Delay(5);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(paddle_tex);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_Quit();
    
    return 0;
}

void drawFrame(SDL_Renderer *ren, SDL_Texture *paddle_tex, SDL_Texture *ball_tex)
{
    SDL_Rect rc1 = { game.player1.x, game.player1.y, game.player1.width, game.player1.height };
    SDL_Rect rc2 = { game.player2.x, game.player2.y, game.player2.width, game.player2.height };
    SDL_Rect ballrc = { game.ball.x, game.ball.y, game.ball.w, game.ball.h };
    
    SDL_RenderCopy(ren, paddle_tex, 0, &rc1);
    SDL_RenderCopy(ren, paddle_tex, 0, &rc2);
    SDL_RenderCopy(ren, ball_tex, 0, &ballrc);
    
}

void procGame(Paddle &one, Paddle &two, Ball &ball, int speed) {
    
    
    if(ball.dir == 1 && ball.x > 5 && ball.y > 17) {
        
        if(ball.x == one.x + 10 && ball.y >= one.y && ball.y <= one.y + 100)
            ball.dir = rand()%2 + 3;
        else {
            ball.x -= speed;
            ball.y -= speed;
        }
    }
    else if(ball.dir == 2 && ball.x > 5 && ball.y < 480) {
        
        if(ball.x == one.x + 10 && ball.y >= one.y && ball.y <= one.y + 100)
            ball.dir = rand()% 2 + 3;
        else {
            ball.x -= speed;
            ball.y += speed;
        }
    }
    else if(ball.dir == 3 && ball.x < 640 && ball.y > 17) {
        
        if(ball.x > 610)
            ball.dir = rand()%2 + 1;
        else {
            ball.x += speed;
            ball.y -= speed;
        }
    }
    else if(ball.dir == 4 && ball.x < 640 && ball.y < 480) {
        
        if(ball.x > 610)
            ball.dir = rand()% 2 + 1;
        else {
            ball.x += speed;
            ball.y += speed;
        }
    }
    else {
        if(ball.dir == 1 || ball.dir == 3) ball.dir++;
        else if(ball.dir == 2 || ball.dir == 4) ball.dir--;
    }
    
    if(ball.x < 6) {
        ball.x = 315;
        ball.y = 240;
        ball.dir = 1+(rand()%4);
        two.score();
    }
    
}
