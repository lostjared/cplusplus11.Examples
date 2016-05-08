//
//  TileMap.h
//  TileMap
//
//  Created by Jared Bruni on 6/8/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//

#ifndef __TileMap__TileMap__
#define __TileMap__TileMap__

#include <iostream>
#include <string>
#include <vector>

namespace grid {

    class OutOfRange {
    public:
        OutOfRange() = default;
    };
    
    
    template<typename GridType>
    class GridObject {
    public:
        GridType type;
        signed int x, y,w,h,state,grid;
        std::string text;
        ~GridObject() { }
        GridObject() : x{}, y{}, w{}, h{}, state{}, grid{}, text{} {}
        GridObject(signed int cx, signed int cy, signed int cw, signed int ch) : x(cx), y(cy), w(cw), h(ch) {}
        GridObject(const GridType &gtype) : type{gtype}, x{}, y{}, w{}, h{}, state{}, grid{}, text{} {}
        std::string getText() const { return text; }
        void setText(const std::string txt) { text = txt; }
    };
    
    enum class Direction { LEFT, RIGHT, DOWN, UP };
    
    template<typename GridType>
    class TileMap {
    public:
        
        TileMap() : tile_width{0}, tile_height{0}, grid(nullptr), scroll_x(0), scroll_y(0) {}
        
        TileMap(signed int width, signed int height) : grid(nullptr), scroll_x(0), scroll_y(0) {
            initToSize(width, height);
            tile_width = width;
            tile_height = height;
        }
        ~TileMap() {
            clean();
        }
        
        void clean() noexcept {
            if(grid != nullptr) {
                for(signed int i = 0; i < tile_width; ++i)
                    delete [] grid[i];
                
                delete [] grid;
                grid = nullptr;
            }
        }
        
        bool loadLevel(std::string filename) {
            /* loop through arrays from passing from file */
            return true;
        }
        
        bool scroll(const Direction dir) {
            
            
            // todo
            switch(dir) {
                case Direction::LEFT:
                    break;
                case Direction::RIGHT:
                    break;
                case Direction::UP:
                    break;
                case Direction::DOWN:
                    break;
            }
            
            
            return true;
        }
        // range checked array access
        GridType &operator()(unsigned int pos_x, unsigned int pos_y) {
            if(pos_x >= 0 && pos_x < tile_width && pos_y >= 0 && pos_y < tile_height)
            return grid[pos_x][pos_y].type;
            
            throw OutOfRange();
        }
        
        GridObject<GridType> &objectAt(unsigned int pos_x, unsigned int pos_y) {
            return grid[pos_x][pos_y];
        }
        
        const signed int width() const { return tile_width; }
        const signed int height() const { return tile_height; }
        
        
        template<typename F>
        void applyFunction(F f) {
            for(signed int i = 0; i < tile_width; ++i) {
                for(signed int z = 0; z < tile_height; ++z) {
                    f(grid[i][z]);
                }
            }
        }
    protected:
        signed int tile_width,tile_height;
        signed int scroll_x, scroll_y;
        
        GridObject<GridType> **grid;
        
        void initToSize(signed int width, signed int height) {
            clean();
            grid = new GridObject<GridType>*[width];
            for(signed int i = 0; i < width; ++i)
                grid[i] = new GridObject<GridType>[height];
            
            for(signed int i = 0; i <width; ++i) {
                for(signed int z = 0; z < height; ++z) {
                    grid[i][z].x = i;
                    grid[i][z].y = z;
                    grid[i][z].state = 0;
                }
            }
        }
    
        
    };
    
}



#endif /* defined(__TileMap__TileMap__) */
