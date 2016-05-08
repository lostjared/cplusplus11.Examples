//
//  main.cpp
//  TileCore
//
//  Created by Jared Bruni on 6/19/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//

#include <iostream>
#include "Tilemap.h"

class Bitmap {};

void draw(int x, int y, mx::Tile<Bitmap> &b) {
    
    std::cout << "Draw at x,y " << x << ", " << y << "\n";
}

int main(int argc, const char * argv[])
{
    try {
        
        mx::TileMap<mx::Tile<Bitmap>> map(640/4, 480/4);
        
        for(signed int x = 0; x < map.width(); ++x) {
            for(signed int y = 0; y < map.height(); ++y) {
                
                mx::Tile<Bitmap> &b = map.at(x,y);
                draw(x,y,b);
            }
        }
    }
    catch (mx::OutOfRange_Exception &e) {
        std::cout << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Error \n";
    }
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

