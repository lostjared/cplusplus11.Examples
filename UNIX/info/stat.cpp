#include<iostream>
#include<sys/stat.h>

int main(int argc, char **argv) {
    if(argc == 2) {
        struct stat sb;
        if(stat(argv[1], &sb) == -1) {
            std::cerr << "Error on stat function.\n";
            exit(EXIT_FAILURE);
        }
        switch(sb.st_mode & S_IFMT) {
            case S_IFREG:
                std::cout << "Regular file..\n";
                break;
            case S_IFDIR:
                std::cout << "Directory..\n";
                break;
            case S_IFCHR:
                std::cout << "Character device..\n";
                break;
            case S_IFBLK:
                std::cout << "Block Device..\n";
                break;
            case S_IFLNK:
                std::cout << "Soft link..\n";
                break;
            case S_IFIFO:
                std::cout << "FIFO or pipe..\n";
                break;
            case S_IFSOCK:
                std::cout << "Socket..\n";
                break;
            default:
                std::cout << "Unknown file type..\n";
        }
    } else {
        std::cerr << "Requires one argument file\n" <<
        argv[0] << " filename\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}
