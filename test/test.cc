#include<iostream>
#include<initializer_list>

class Color {
	
	union {
		unsigned int color;
		unsigned char rgb[4];
				
	} col;
	
public:
	
	Color();
	Color(int color);
	Color(const Color &c);
	Color(std::initializer_list<unsigned char> color);
	
	void operator=(const Color &c);
    void operator=(std::initializer_list<unsigned char> list);
	unsigned char &operator[](unsigned int offset);
	const unsigned int color() const;
	
	void printColor(std::ostream &out);
	void setColor(unsigned int color);
	
	friend std::ostream &operator<<(std::ostream &out, Color &c);
};


Color::Color() {
	col.color = 0;
}

Color::Color(int color) {
	col.color = color;
}

Color::Color(const Color &c) {
	col = c.col;
}

Color::Color(std::initializer_list<unsigned char> color) {
	if(color.size()>3) {
		auto c = color.begin();
		col.rgb[0] = *c;
		col.rgb[1] = *(c+1);
		col.rgb[2] = *(c+2);
		col.rgb[3] = *(c+3);
		
	} else {
		col.color = 0;
	}
}

void Color::operator=(const Color &c) {
	col = c.col;
}

void Color::operator=(std::initializer_list<unsigned char> list) {
    if(list.size()>3) {
		auto c = list.begin();
		col.rgb[0] = *c;
		col.rgb[1] = *(c+1);
		col.rgb[2] = *(c+2);
		col.rgb[3] = *(c+3);
		
	} else {
		col.color = 0;
	}
}

unsigned char &Color::operator[](unsigned int pos) {
	return col.rgb[pos];
}

const unsigned int Color::color() const {
	return col.color;
}

void Color::printColor(std::ostream &out) {
	out << "r: " << int(col.rgb[0]) << " g: " << int(col.rgb[1]) << " b: " << int(col.rgb[2]);
}

void Color::setColor(unsigned int color) {
	col.color = color;
}

std::ostream &operator<<(std::ostream &out, Color &c) {
	
	c.printColor(out);
	return out;
}


int main(int argc, char **argv) {

	Color color({0xFF,0xFF,0xFF, 0});
	std::cout << "Value: " << color << " or " << std::ios::hex << color.color() << "\n";
    color = { 0xFF, 0xFF, 0xFF, 0xFF };
    std::cout << "Value: " << color << " or " << std::ios::hex << color.color() << "\n";
	return 0;
}