# Jared Bruni's C++11 Examples

Newly generated website interface for these examples:

https://lostsidedead.biz/cplusplus/11/

Last updated: 2026-03-04


This collection is my way of navigating through, and reinforcing my understanding of, C++11's new functionalities. I no longer plan to write a repository for C++14 as I have one for C++17.

The primary purpose of these examples is to showcase specific C++11 features rather than to provide practical utility. However, a few examples are designed to address real tasks, such as creating m3u playlists or generating HTML for CGI applications.

Included among the examples is a calculator that parses expressions, reminiscent of the one featured in "The C++ Programming Language" 4th Edition.

## Compilation Instructions

### Recommended (CMake, Linux/macOS)

From the `cplusplus11.Examples` directory:

```bash
cmake -S . -B build-cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-cmake -j$(nproc)
```

SDL behavior with CMake:

- SDL2 demos are built when the SDL2 package is found.
- If SDL2 is not found, SDL-dependent demos are skipped automatically.
- Legacy SDL1-only demo(s) are disabled by default. Enable them with:

```bash
cmake -S . -B build-cmake -DBUILD_LEGACY_SDL1_DEMOS=ON
```

Build with strict warnings:

```bash
cmake -S . -B build-cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build-cmake -j$(nproc)
```

Run one target example:

```bash
./build-cmake/main_main_cpp
```

### Legacy Makefiles

#### macOS

```bash
make
```

#### Linux

```bash
make -f Makefile.linux
```

## Compilation Note
Ensure your compiler is C++11 compatible. When using clang, for instance, compile a source file with:

```bash
clang++ -std=c++11 sourcefile.cc -o sourcefile
```

On Linux, opt for libstdc++ and use g++ version 4.8 or newer. Compiling any program requires just a single line:

```bash
g++ -std=c++11 sourcefile.cc -o sourcefile
```

For shared library examples on Linux, use `.so` (not `.dylib`):

```bash
g++ -std=c++11 -fPIC -shared lib.cpp -o libdemo.so
g++ -std=c++11 prog.cpp -o program -L. -ldemo
LD_LIBRARY_PATH=. ./program
```

- Jared Bruni
