//
//  main.cpp
//  TileMap
//
//  Created by Jared Bruni on 6/8/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//
#include "TileMap.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class TileBitmap {
public:

    TileBitmap() : x{}, y{}, w{}, h{} {
        
    }

    ~TileBitmap() {
        // clean up bitmap
    }
    signed int x, y, w, h;
    
    bool loadImage(std::string s) {
        fileName = s;
        // load image
        return true;
    }
    
    void setCoords(int cx, int cy, int cw, int ch) {
        x = cx;
        y = cy;
        w = cw;
        h = ch;
    }
    
    void draw() {
        // draw at x,y by w,h
    }
    
    const std::string getFileName() const { return fileName; }
    
protected:
    std::string fileName;
};

class TileObject {
public:
    TileObject()  { }

    bool loadFile(std::string s) {
        TileBitmap *bmp = new TileBitmap();
        if(bmp->loadImage(s))
            bitmaps.push_back(std::unique_ptr<TileBitmap>(bmp));
        else {
            delete bmp;
            return false;
        }
        return true;
    }
    
    void draw() {
        for(auto &i : bitmaps) {
            i.get()->draw();
        }
    
    }
 
protected:
    std::vector<std::unique_ptr<TileBitmap>> bitmaps;
    
};

int main(int argc, const char * argv[])
{
    try {
        int width = 640/4, height = 480/4;
        grid::TileMap<TileObject> tiles(width, height);
     
        for(int i = 0; i < width; ++i) {
            for(int z = 0; z < height; ++z) {
                grid::GridObject<TileObject> &tileAt = tiles.objectAt(i, z);
                tileAt.setText("Object ");
                tileAt.type.draw();
                std::cout << tileAt.getText() << "\n";
            }
        }
    } catch(grid::OutOfRange &e) {
        std::cerr << "Error array access out of range.\n";
    } catch (...) {
        std::cerr << "Unhanlded Exception.\n";
    }
    return 0;
}

