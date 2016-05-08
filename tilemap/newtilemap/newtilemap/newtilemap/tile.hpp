/* written by Jared Bruni
 * http://lostsidedead.com
 */

#ifndef __TILE_H__
#define __TILE_H__
#include<array>

namespace tilemx {

    using value_int = unsigned int;
    
    template<typename T>
    class Tile {
    protected:
        T tile;
        using value_type = T;
    public:
        value_int x,y,w,h,offset;
        Tile() = default;
        Tile(T t) : tile(t), x{}, y{},w{},h{},offset{} {}
        T &value() { return tile; }
    };
    
    template<typename T, int N>
    class TileRow {
    public:
        const int Length = N;
        TileRow() = default;
        TileRow(const TileRow<T,N> &rowc) {
            for(value_int i = 0; i < N; ++i)
                row_value[i] = rowc.row_value[i];
        }
        TileRow(std::initializer_list<T> tiles) : row_value{tiles} {}
        T &row(value_int val) { return row_value[val]; }
        T &operator[](value_int val) { return row_value[val]; }
        const int size() { return N; }
    protected:
        std::array<T,N> row_value;
    };
    
    template<typename T, int W, int H>
    class TileMatrix {
    protected:
        value_int posX,posY;
        TileRow<TileRow<Tile<T>,W>,H> tiles;
    public:
        TileMatrix() : posX{}, posY{} { }
        TileMatrix(TileMatrix<T,W,H> &tm) : posX{tm.posX}, posY{tm.posY} {
            for(value_int i = 0; i < W; ++i) {
                for(value_int z = 0; z < H; ++z) {
                    tileAt(i, z) = tm.tileAt(i, z);
                }
            }
        }
        
        const value_int offsetX() { return posX; }
        const value_int offsetY() { return posY; }
        
        void initCoords(const value_int tSize) {
            applyFunction([&](const value_int x, const value_int y, Tile<T> &tile) { tile.x = x*tSize; tile.y = y*tSize; tile.w = tSize; tile.h = tSize; });
        }
        
        template<typename F>
        void applyFunction(F f) {
            for(value_int i = 0; i < W; ++i) {
                for(value_int z = 0; z < H; ++z) {
                    f(i,z,tileAt(i,z));
                }
            }
        }
        
        virtual void draw() { }
        
        void returnHome() {
            posX = posY = 0;
        }
        
        Tile<T> &tileAt(const value_int x, const value_int y) {
            return tiles[y][x];
        }
        
        virtual void scroll_left() {
            if(posX > 0) --posX;
        }
        virtual void scroll_right(const value_int screenX) {
            if(posX < W-screenX) ++posX;
        }
        virtual void scroll_up() {
            if(posY > 0) --posY;
        }
        virtual void scroll_down(const value_int screenY) {
            if(posY < H-screenY) posY++;
        }
    };

}



#endif

