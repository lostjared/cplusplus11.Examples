/* virutal base demo

 http://lostsidedead.com
 
 Jared Bruni
 
 C++11 Code Example
 
*/


#include<iostream>
#include<string>

namespace ui {

    class Widget {
    public:
        Widget(const Widget &);
        Widget(Widget &);
        Widget(unsigned int, signed int, signed int, signed int, signed int);
        virtual ~Widget() { }
        virtual void draw() = 0;
        virtual void init() = 0;
        
    protected:
        unsigned int type;
        signed int cx, cy, cw, ch;
        void setWidget(const Widget &);
    };

    
    Widget::Widget(const Widget &w) {
        setWidget(w);
    }
    
    Widget::Widget(Widget &w) {
        setWidget(w);
    }
    
    Widget::Widget(unsigned int t, signed int x, signed int y, signed int w, signed int h) : type{t}, cx{x}, cy{y}, cw{w}, ch{h} { std::cout << "Widget constructor.\n"; }
    
    void Widget::setWidget(const Widget &w) {
        cx = w.cx;
        cy = w.cy;
        cw = w.cw;
        ch = w.ch;
        type = w.type;
    }
    
    
    // a virtual base is included once
    class Text : public virtual Widget {
    public:
        Text(std::string text, signed int x, signed int y);
        void draw() override;
        void init() override;
    protected:
        std::string text;
    };

    Text::Text(std::string txt, signed int x, signed int y) : Widget{2,x,y,0,0}, text{txt}  {
        
    }
    
    void Text::draw() {
        std::cout << "Draw Text: " << text << " at : " << cx << ":" << cy << "\n";
        
    }
    
    void Text::init() {
        std::cout << "Text Init...\n";
    }
    // also from Widget
    class Button : public virtual Widget {
    public:
        Button(signed int bx, signed int by, signed int bw, signed int bh);
        void setText(const std::string &text);
        std::string getText() const;
        void draw() override;
        void init() override;
    protected:
        std::string text;
        
    };
    
    Button::Button(signed int bx, signed int by, signed int bw, signed int bh) : Widget(1, bx, by, bw, bh) {}
    
    void Button::setText(const std::string &txt) {
        text = txt;
    }
    
    std::string Button::getText() const { return text; }
    
    void Button::draw() {
        std::cout << "Draw button at " << cx << ":" << cy << " size: " << cw << "," << ch <<"\n";
    }
    
    void Button::init() {
        std::cout << "Initialize button\n";
    }
    
    // Multiple inheritance using both Text and Button which both inherit from Widget
    class ToolButton : public Text, public Button {
    public:
        ToolButton(std::string t, signed int x, signed int y, signed int w, signed int h);
        void draw() override;
        void init() override;
        
    };

    //Widget's constructor is only called once
    ToolButton::ToolButton(std::string t, signed int x, signed int y, signed int w, signed int h) : Widget{3,x,y,w,h}, Text{t,x,y}, Button{x,y,w,h} {
        
    }

    void ToolButton::draw() {
        Button::draw();
        Text::draw();
    }
    
    void ToolButton::init() {
        Button::init();
        Text::init();
    }
    
}



int main(int argc, char **argv) {
    try {
        
        ui::ToolButton button1("Hello world", 25, 25, 100, 100);
        button1.init();
        button1.draw();
        // set text value
        button1.setText(" Toolbutton ");
        // print text value
        std::cout << button1.getText() << "\n";
        
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error.\n";
    }
    
    return 0;
}