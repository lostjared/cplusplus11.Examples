#include"memfile.hpp"
#include"image_res/floyd.h"


int main(int argc, char **argv) {
    
    mem::binOutputArray("floyd.jpg", floyd_jpg, floyd_jpg_length);

    return 0;
}
