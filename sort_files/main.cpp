#include"sfile.hpp"


int main(int argc, char **argv) {
    FileSort file_sort;
    for(unsigned int i = 1; i < argc; ++i) {
        file_sort.addFile(argv[i]);
    }
    
    file_sort.sortAndOutput("sorted_text.txt");
    return 0;
}