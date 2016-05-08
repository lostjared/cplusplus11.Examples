#ifndef __STATIC_MAIN_H__
#define __STATIC_MAIN_H__


#define STATIC_MAIN(X) int main(int argc, char **argv) { return X::main(argc, argv); }

#endif
