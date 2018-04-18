#include<iostream>
#include<unistd.h>

int main(int argc, char **argv) {
    if(argc > 1) {
        int opt;
        std::cout << "Argument options...\n";
        while((opt = getopt(argc, argv, "cxi:")) != -1) {
            switch(opt) {
                case 'c':
                    std::cout << "c option\n";
                    break;
                case 'x':
                    std::cout << "x option\n";
                    break;
                case 'i':
                    std::cout << "i option: " << optarg << "\n";
                    break;
            }
        }
    }
    return 0;
}
