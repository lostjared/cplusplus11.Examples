//
//  Tilemap.h
//  TileCore
//
//  Created by Jared Bruni on 6/19/13.
//  Copyright (c) 2013 Jared Bruni. All rights reserved.
//

#ifndef __TileCore__Tilemap__
#define __TileCore__Tilemap__

#include<iostream>
#include<vector>
#include<memory>

namespace mx {
    
    
    class OutOfRange_Exception : public std::exception {};
    class SizeError_Exception : public std::exception {};
    
    template<typename T>
    class Tile {
    public:
        std::vector<std::unique_ptr<T>> tile;
        signed int x,y,w,h,frame,direction;
        
        Tile(std::initializer_list<T> &t) : tile {t} {
            
        }
        
        Tile(const T *type) {
            tile.push_back(type);
        }
        
        void operator=(const T *type) {
            tile.push_back(type);
        }
        
        void operator+=(const T *type) {
            tile.push_back(type);
        }
        
        Tile() : tile {} {
            
        }
        // have level editor write to file then read and call this
        void pushBack(T *type) {
            tile.push_back(type);
        }
    
    };
    
    template<typename T>
    class TileMap {
    public:
        signed int tile_w, tile_h;
        TileMap() : tile_w(0), tile_h(0), tile_map(nullptr) {}
        TileMap(const TileMap &t) = delete;
        TileMap(signed int cw, signed int ch) : tile_w(cw) , tile_h(ch), tile_map(nullptr) {
             sizeMap(cw, ch);
        }
        ~TileMap() {
            clearMap();
        }
        
        T &operator()(signed int x, signed int y) {
            return at(x,y);
        }
        
        T &at(signed int x, signed int y) {
            if(x >= 0 && x < tile_w && y >= 0 && y < tile_h)
                return tile_map[x][y];
            
            throw OutOfRange_Exception();
        }
        
        const signed int width() const { return tile_w; }
        const signed int height() const { return tile_h; }
        
        T **rootPtr() const { return tile_map; }
        
    protected:
        
        void clearMap() noexcept {
            if(tile_map != nullptr) {
                for(signed int i = 0; i < tile_w; ++i)
                    delete [] tile_map[i];
                
                delete [] tile_map;
                tile_map = nullptr;
            }
        }
        
        void sizeMap(signed int w, signed int h) {
            clearMap();
            tile_w = w;
            tile_h = h;
            tile_map = new T*[w];
            for(signed int i = 0; i < w; ++i) {
                tile_map[i] = new T[h]();
            }
            for(signed int i = 0; i < tile_w; ++i) {
                for(signed int z = 0; z < tile_h; ++z) {
                    T &type = at(i, z);
                    type.x = i;
                    type.y = z;
                }
            }
        }
        
    private:
        T **tile_map;
    };
    
    
}


#endif /* defined(__TileCore__Tilemap__) */
