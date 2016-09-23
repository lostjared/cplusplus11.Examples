#include<iostream>
#include<sys/xattr.h>
#include<cstring>

constexpr int LIST_SIZE=10000;

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Error requires an argument\n" << argv[0] << " file\n";
        exit(EXIT_FAILURE);
    }
    
    
    char attr_list[LIST_SIZE], attr_value[LIST_SIZE];
    ssize_t list_len = 0, value_len = 0;
    int cur_pos, i, z;
#if defined(__APPLE__)
    list_len = listxattr(argv[1], attr_list, LIST_SIZE, XATTR_NOFOLLOW);
#elif defined(__linux__)
    list_len = listxattr(argv[1], attr_list, LIST_SIZE);
#endif
    
    if(list_len == 1) {
        std::cerr << "Error extend attribute list failed.\n";
        exit(EXIT_FAILURE);
    }
    
    std::cout << argv[1] << ":\n";
    
    for(cur_pos = 0; cur_pos < list_len; cur_pos += strlen(&attr_list[cur_pos])+1) {
        std::cout << "name = " << &attr_list[cur_pos] << "\n";
#if defined(__APPLE__)
        value_len = getxattr(argv[1], &attr_list[cur_pos], attr_value,LIST_SIZE, 0, XATTR_NOFOLLOW);
#elif defined(__linux__)
        value_len = getxattr(argv[1], &attr_list[cur_pos], attr_value,LIST_SIZE);
#endif
        
        if(value_len == -1) {
            std::cout << "Could not get value..\n";
        } else {
            std::cout << "value = " << attr_value << "\n";
        }
        
        std::cout << "\n";
    }
    
    return EXIT_SUCCESS;
}
