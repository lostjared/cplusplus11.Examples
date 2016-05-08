//
//  main.cpp
//  afhd_x
//
//  Created by Jared Bruni on 7/8/12..
//  a way to create individual effects, each effect can have its own varibles


#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>

class FilterContainer {
protected:
    void *buffer;
    int width, height, buffer_width;
public:
    FilterContainer(void *buf, unsigned int w, unsigned int h, unsigned int width) : buffer(buf), width(w), height(h), buffer_width(width) { }
    virtual ~FilterContainer() {
        static unsigned int counter=0;
        ++counter;
        std::cout << "effect " << counter << " deleted\n";
    }
    virtual void proc() = 0;
    void operator()() { proc(); }
};

template<typename FilterType> class  Processor {
    std::vector<std::unique_ptr<FilterType>> filterType;
public:
    Processor() = default;
    Processor(Processor &p) = delete;
    void operator=(Processor &p) = delete;

    
    ~Processor() { 
        std::cout << "Processor unloaded\n";
    }
    
   // void initFilters((std::initializer_list<FilterType> t) {
   //     filterType = t;
   // }
    
    void addFilter(FilterType *cont) {
        filterType.push_back(std::unique_ptr<FilterType>(cont));
    }
    
    FilterContainer &operator[](unsigned int pos) {
        return filterType[pos];
    }
    
    void procFilters() {
         for(auto &it : filterType) {
             it.get()->proc();
        }
    }
    const unsigned int size() { return filterType.size(); }
    
};

// so each transformation is a individual class

class Triblend : public FilterContainer {
public:
    explicit Triblend(void *buf, int w, int h, int width) : FilterContainer(buf,w,h,width) { }
    virtual void proc() {
        /*
         unsigned int *buffer_x = (unsigned int *)buffer;
         */
        static unsigned int buf_num=0;
        std::cout << "proccess buffer some unique way: " << "#" << (++buf_num) << "\n";
        
    }
    
};

class Mem_Blend : public FilterContainer {
public:
    explicit Mem_Blend(void *buf, int w, int h, int width) : FilterContainer(buf,w,h,width) {}
    virtual void proc() {
        std::cout << "another one Memblend #2" << "\n";
    }
    
};


int main(int argc, char **argv) {
    
    try {
        void *buffer = 0;
        int b_width = 0;
        int b_height = 0;
        int buffer_width= 0;
    
        // we create the object that calls the filters
        Processor<FilterContainer> proc;
    
        // for a example we
        // add 4 calls to Triblend objects
        for(int i=0; i<4; ++i)
            proc.addFilter(new Triblend(buffer, b_width, b_height, buffer_width));
    
        // add a Another effect to the list
        proc.addFilter(new Mem_Blend(buffer,b_width,b_height,buffer_width));
    
        proc.procFilters();
    
        // create output image
    
    } catch( std::exception &e ) {
        std::cerr << e.what() << std::endl;
        
    } catch( ... ) {
        std::cerr << "Unknown exception..\n";
    }
        
    return 0;
}

