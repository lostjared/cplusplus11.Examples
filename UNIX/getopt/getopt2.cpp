#include<iostream>
#include<unistd.h>

class Program {
public:
    Program(unsigned int c) : count(c) {}
    void run();
private:
    unsigned int count;
};

void Program::run() {
    for(unsigned int i = 0; i < count; ++i) {
        std::cout << "Hello World with getopt!.\n";
    }
}

int main(int argc, char **argv) {
    if(argc > 1) {
        int opt;
        unsigned int counter = 0;
        while((opt = getopt(argc, argv, "c:")) != -1) {
            switch(opt) {
                case 'c':
                    counter = atoi(optarg);
                    if(counter == 0) {
                        std::cerr << "Error requires loop count...\n";
                        exit(EXIT_FAILURE);
                    }
                    break;
                default:
                    std::cout << " use -c counter\n";
                    exit(0);
                    break;
            }
        }
        Program program(counter);
        program.run();
    } else {
        std::cerr << "use: " << argv[0] << " -c counter\n";
    }
    return 0;
}
