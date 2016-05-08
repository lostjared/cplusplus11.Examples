/*

some C++11
written by Jared Bruni
http://lostsidedead.com

*/


#include<iostream>
#include<iomanip>
#include<array>


namespace mx {

    // RGBA color value
    class Color {
    public:
        Color();
        Color(const Color &);
        Color(unsigned char,unsigned char,unsigned char,unsigned char);
        Color(unsigned int color);
        
        const unsigned int value() const { return color_value; }
        unsigned char &operator[](unsigned int i) { return colors[i]; }
        
        bool operator==(const Color &c);
        bool operator==(unsigned int c);
        bool operator!=(unsigned int c);
        bool operator!=(const Color &c);
        Color &operator=(const Color &c);
        Color &operator=(unsigned int c);
        const std::initializer_list<unsigned char> rgb() {
            return {colors[0], colors[1], colors[2], colors[3]};
        }
        
    protected:
        static_assert(sizeof(unsigned int)==4, "Wrong size int");
        static_assert(sizeof(unsigned char)==1, "Wrong size char");
        
        union {
            unsigned char colors[sizeof(unsigned int)];
            unsigned int color_value;
        };
    
    };
    
    Color::Color() : color_value{} {

    }
    
    Color::Color(const Color &c) : color_value(c.color_value) {
   
    }
    
    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
        colors[3] = a;
    }
    
    bool Color::operator==(const Color &c) {
        if(color_value == c.color_value) return true;
        return false;
    }
    
    
    bool Color::operator==(unsigned int c) {
        if(color_value == c) return true;
        return false;
    }
    
    bool Color::operator!=(const Color &c) {
        return (!operator==(c));
    }
    
    bool Color::operator!=(unsigned int c) {
        return (!operator==(c));
    }
    
    Color &Color::operator=(const Color &c) {
        color_value = c.color_value;
        return *this;
    }
    
    Color &Color::operator=(unsigned int c) {
        color_value = c;
        return *this;
    }
    
    std::ostream &operator<<(std::ostream &out, const Color &c) {
        out << "Value of color is: " << std::setw(10) << c.value() << "\n";
        return out;
    }
}


int main(int argc, char **argv) {
    
    float alpha = 1.4f;
    // create a multidimensional array of mx::Color
    std::array<std::array<mx::Color, 640>, 480> colors;
    for(int x = 0; x < 640; ++x) {
        for(int y = 0; y < 480; ++y) {
            for(int i = 0; i < 4; ++i) {
            colors[y][x][i] = rand()%255;
                std::cout << " set color to random at " << std::setw(4) << x << " " << std::setw(4) << y << ": " << i << " " << colors[y][x] << "\n";
            }
            mx::Color &color_manip = colors[y][x];
            color_manip[0] *= alpha;
            color_manip[1] *= alpha;
            color_manip[2] *= alpha;
            color_manip[3] = 255;
            
            alpha += 0.1f;
            std::cout << "after manipulation color equals: " << color_manip << "\n";
        }
    }
    
    return 0;
    
}