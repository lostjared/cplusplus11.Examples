#include<iostream>
#include<vector>

// container class for filter functions
class FilterContainer {
public:
    using Filter = void (*)(unsigned char *pixels);
    FilterContainer() = default;
    int addFilter(Filter f) {
        filters.emplace_back(f);
        return filters.size()-1;
    }
    void operator()(int filterID, unsigned char *pixels) {
        filters[filterID](pixels);
    }
protected:
    std::vector<Filter> filters;
};


int main(int argc, char **argv) {
    FilterContainer f;
    int selfAlpha = f.addFilter( [](unsigned char *pixels) {
        std::cout << "selfAlphaBlend..\n";
    });
    int diamond = f.addFilter( [] (unsigned char *pixels) {
        std::cout << "diamond Pattern\n";
    });
    
    unsigned char buffer[1024]; // would be the image pixels or cv::Mat if OpenCV
    // call the functions through the FilterContainer interface
    f(selfAlpha, buffer);
    f(diamond, buffer);
                              
    return 0;
}