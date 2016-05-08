/*
 written by Jared Bruni
 http://lostsidedead.com
*/
#include"3card.hpp"

const int Width = 1280, Height = 720;
void updateScreen();
void initTextures();
void freeTextures();

bool moving = false;
bool shuffled = true;

SDL_Texture *display_textures[6];
SDL_Rect display_cords[6];
void initFontTextures(TTF_Font *font);

int main(int argc, char **argv) {
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initalizing: " << SDL_GetError() << "\n";
        return -1;
    }
    
    if(TTF_Init() < 0) {
        std::cerr << "Error initializing fonts: " << TTF_GetError() << "\n";
        SDL_Quit();
        return -1;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    
    Shuffle shuffle;
    
    SDL_Window *window = SDL_CreateWindow("3card", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == 0) {
        std::cerr << SDL_GetError() << "\n";
        return -1;
    }
    
    initTextures();
    
    TTF_Font *font = TTF_OpenFont("img/font.ttf", 24);
    
    if(!font) {
        std::cerr << "Error loading font: " << TTF_GetError() << "\n";
        SDL_Quit();
        return -1;
    }
    
    initFontTextures(font);
    
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Width, Height);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(NULL, Width, Height, 32, 0, 0x00FF0000, 0x0000FF00,0x000000FF,0xFF000000);

    bool active = true;
    SDL_Event e;
    int index = 0;
    bool show_win = false;
    
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    
                    switch(e.key.keysym.sym) {
                        case SDLK_RETURN:
                            if(shuffled == false) continue;
                            
                            if(moving == false) {
                                shuffle.startShuffle();
                                moving = true;
                                index = 1;
                            }
                            else {
                                moving = false;
                                shuffle.set();
                                index = 3;
                                
                            }
                            break;
                        case SDLK_SPACE: {
                            if(moving == false && shuffled == false) {
                                shuffle.shuffle();
                                shuffled = true;
                                index = 0;
                                show_win = false;
                            }
                        }
                            break;
                    }
                    
                    if(shuffled == true && moving == false) {
                        switch(e.key.keysym.sym) {
                            case SDLK_1:
                                shuffle.show(0);
                                shuffled = false;
                                show_win = true;
                                index = 2;
                                break;
                            case SDLK_2:
                                shuffle.show(1);
                                shuffled = false;
                                show_win = true;
                                index = 2;
                                break;
                            case SDLK_3:
                                shuffle.show(2);
                                shuffled = false;
                                show_win = true;
                                index = 2;
                                break;
                        }
                    }
                    
                    break;
            }
        }
        
        if(moving == true)
            shuffle.move();
        
        SDL_RenderClear(ren);
        
        SDL_Rect rc1 = { 25, 25, display_cords[index].w, display_cords[index].h};
        SDL_RenderCopy(ren, display_textures[index], 0, &rc1);

        if(show_win) {
            int index;
            
            if(shuffle.won()==true)
                index = 4;
            else
                index = 5;
            
            SDL_Rect rc1 = { 25, 70, display_cords[index].w, display_cords[index].h };
            SDL_RenderCopy(ren, display_textures[index], 0, &rc1);

        }
        
        shuffle.draw();
        SDL_RenderPresent(ren);
    }
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyTexture(tex);
    freeTextures();
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


void setRect(SDL_Rect *rc, SDL_Surface *surface) {
    rc->w = surface->w;
    rc->h = surface->h;
    rc->x = rc->y = 0;
}


SDL_Texture *createTextureFromString(TTF_Font *font, std::string s, SDL_Rect *rc) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Color color = {255,255,255};
    surface = TTF_RenderText_Solid(font, s.c_str(), color);
    if(!surface) {
        std::cerr << "Error creating texture: " << TTF_GetError() << "\n";
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(ren, surface);
    setRect(rc, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void initFontTextures(TTF_Font *font) {
    
    display_textures[0] = createTextureFromString(font, "Press Enter to Shuffle", &display_cords[0]);
    
    display_textures[1] = createTextureFromString(font, "Press Enter to Stop Shuffle", &display_cords[1]);
    
    display_textures[2] = createTextureFromString(font, "Press Space to Reset", &display_cords[2]);
    display_textures[3] = createTextureFromString(font, "Press 1, 2 or 3 to Select Card", &display_cords[3]);
    
    display_textures[4] = createTextureFromString(font, "You Win!", &display_cords[4]);
    display_textures[5] = createTextureFromString(font, "You Lose!", &display_cords[5]);


}

void initTextures() {

    SDL_Surface *cardb = SDL_LoadBMP("img/cardback.bmp"), *carda = SDL_LoadBMP("img/cardace.bmp"), *cardk = SDL_LoadBMP("img/cardking.bmp");
    
    if(cardb == 0 || carda == 0 || cardk == 0) {
        std::cerr <<"Error loading textures..\n";
        exit(-1);
    }
    
    cards[0] = SDL_CreateTextureFromSurface(ren, cardb);
    cards[1] = SDL_CreateTextureFromSurface(ren, carda);
    cards[2] = SDL_CreateTextureFromSurface(ren, cardk);
    SDL_FreeSurface(cardb);
    SDL_FreeSurface(carda);
    SDL_FreeSurface(cardk);
}

void freeTextures() {
    int i;
    for(i = 0; i < 3; ++i) SDL_DestroyTexture(cards[i]);
    for(i = 0; i < 6; ++i) SDL_DestroyTexture(display_textures[i]);
}
