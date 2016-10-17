/* Adapted from "the Linux Programming Interface"
 Chapter 52
 */
#include<iostream>
#include<mqueue.h>

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error argument not given.\n" << argv[0] << " queue\n";
        exit(EXIT_FAILURE);
    }
    if(mq_unlink(argv[1]) == -1) {
        std::cerr << "Could not unlink: " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
