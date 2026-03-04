cmake_minimum_required(VERSION 3.16)

project(cplusplus11_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ---------------------------------------------------------------------------
# Verify the compiler and standard library support C++11 headers/features
# required by the examples.  Fail early with a clear message rather than
# producing hundreds of cryptic errors.
# ---------------------------------------------------------------------------
include(CheckIncludeFileCXX)
include(CheckCXXSourceCompiles)

set(CPP11_REQUIRED_HEADERS
    array
    atomic
    chrono
    condition_variable
    functional
    future
    initializer_list
    memory
    mutex
    random
    regex
    thread
    tuple
    type_traits
    typeindex
    unordered_map
    unordered_set
)

foreach(header IN LISTS CPP11_REQUIRED_HEADERS)
    string(TOUPPER "${header}" header_upper)
    string(REPLACE "/" "_" header_upper "${header_upper}")
    set(var_name "HAS_CXX11_${header_upper}")
    check_include_file_cxx("${header}" ${var_name})
    if(NOT ${var_name})
        message(FATAL_ERROR
            "C++11 header <${header}> not found.\n"
            "Your compiler or standard library is too old to build the examples.\n"
            "Please use GCC >= 4.8, Clang >= 3.3, or MSVC >= 19.0.")
    endif()
endforeach()

# Quick smoke-test that key C++11 language/library features actually work
# (catches misconfigured toolchains that ship the headers but lack support).
check_cxx_source_compiles("
#include <array>
#include <functional>
#include <memory>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>

auto lambda = [](int x) { return x * 2; };

template<typename... Args>
int variadic_sum(Args... args) { int sum = 0; for (auto v : {args...}) sum += v; return sum; }

enum class Color { Red, Green, Blue };

int main() {
    // auto + initializer list
    auto arr = std::array<int, 3>{{1, 2, 3}};
    // lambda
    std::function<int(int)> fn = lambda;
    (void)fn(arr[0]);
    // smart pointers
    auto sp = std::make_shared<int>(42);
    auto up = std::unique_ptr<int>(new int(7));
    // tuple
    auto t = std::make_tuple(1, 2.0, 'a');
    (void)std::get<0>(t);
    // unordered_map
    std::unordered_map<int,int> m{{1,2}};
    (void)m;
    // type traits
    static_assert(std::is_integral<int>::value, \"int must be integral\");
    // range-based for
    for (auto &v : arr) { (void)v; }
    // variadic templates
    (void)variadic_sum(1, 2, 3);
    // scoped enum
    Color c = Color::Red;
    (void)c;
    return 0;
}
" CXX11_FEATURES_WORK)

if(NOT CXX11_FEATURES_WORK)
    message(FATAL_ERROR
        "C++11 feature smoke-test failed.\n"
        "Your compiler claims C++11 support but key features do not compile.\n"
        "Please use GCC >= 4.8, Clang >= 3.3, or MSVC >= 19.0.")
endif()

message(STATUS "C++11 standard library and language feature checks passed")

find_package(Threads REQUIRED)
find_library(CRYPT_LIBRARY crypt)
find_package(SDL2 QUIET)

option(BUILD_LEGACY_SDL1_DEMOS "Build legacy SDL1-only examples" OFF)

if(SDL2_FOUND)
    if(TARGET SDL2::SDL2)
        get_target_property(SDL2_TARGET_INCLUDES SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
        if(SDL2_TARGET_INCLUDES)
            include_directories(${SDL2_TARGET_INCLUDES})
        endif()
    elseif(SDL2_INCLUDE_DIRS)
        include_directories(${SDL2_INCLUDE_DIRS})
    endif()
endif()

function(file_has_main source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "(^|[ \t\r\n])main[ \t\r\n]*\\(" has_main "${source_content}")
    if(has_main)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(make_target_name input_path output_var)
    string(REPLACE "/" "_" target_name "${input_path}")
    string(REPLACE "." "_" target_name "${target_name}")
    string(REPLACE "-" "_" target_name "${target_name}")
    string(REPLACE "+" "x" target_name "${target_name}")
    set(${output_var} "${target_name}" PARENT_SCOPE)
endfunction()

function(link_unix_libs_if_needed target_name source_path)
    if(source_path MATCHES "^UNIX/")
        target_link_libraries(${target_name} PRIVATE Threads::Threads)
        if(CMAKE_DL_LIBS)
            target_link_libraries(${target_name} PRIVATE ${CMAKE_DL_LIBS})
        endif()
        if(source_path MATCHES "^UNIX/user/" AND CRYPT_LIBRARY)
            target_link_libraries(${target_name} PRIVATE ${CRYPT_LIBRARY})
        endif()
    endif()
endfunction()

function(source_uses_sdl source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*SDL[^>\"]*[>\"]" has_sdl_include "${source_content}")
    if(has_sdl_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(link_sdl2_if_needed target_name)
    if(NOT SDL2_FOUND)
        return()
    endif()

    set(needs_sdl FALSE)
    foreach(source_file IN LISTS ARGN)
        source_uses_sdl("${source_file}" has_sdl)
        string(TOLOWER "${source_file}" source_file_lower)
        if(has_sdl)
            set(needs_sdl TRUE)
            break()
        elseif(source_file_lower MATCHES "(^|/)(sdl|sdl2|tilemap)(/|$)")
            set(needs_sdl TRUE)
            break()
        endif()
    endforeach()

    if(needs_sdl)
        if(TARGET SDL2::SDL2)
            target_link_libraries(${target_name} PRIVATE SDL2::SDL2)
        elseif(SDL2_LIBRARIES)
            target_link_libraries(${target_name} PRIVATE ${SDL2_LIBRARIES})
        endif()
    endif()
endfunction()

function(add_unix_shared_example example_name link_with_demo)
    set(example_root "UNIX/shared/${example_name}")
    set(lib_source "${example_root}/lib.cpp")
    set(prog_source "${example_root}/prog.cpp")

    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${lib_source}" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${prog_source}")
        return()
    endif()

    set(lib_target "unix_shared_${example_name}_demo")
    set(prog_target "unix_shared_${example_name}_program")
    set(output_dir "${CMAKE_BINARY_DIR}/UNIX/shared/${example_name}")

    add_library(${lib_target} SHARED "${lib_source}")
    set_target_properties(${lib_target} PROPERTIES
        OUTPUT_NAME demo
        LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
    )

    add_executable(${prog_target} "${prog_source}")
    set_target_properties(${prog_target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
    )

    target_link_libraries(${prog_target} PRIVATE Threads::Threads)

    if(link_with_demo)
        target_link_libraries(${prog_target} PRIVATE ${lib_target})
    elseif(CMAKE_DL_LIBS)
        target_link_libraries(${prog_target} PRIVATE ${CMAKE_DL_LIBS})
    endif()
endfunction()

set(EXAMPLE_ROOTS
    algorithm
    allocator
    array
    arraybyte
    assert
    auto
    bin_to_array
    bitmask
    bitset
    calculator
    cast
    cgi
    chrono
    compile_test
    compress_code
    constexpr
    databyte
    db
    download
    enum
    finally
    find
    friend
    fstream
    function_objects
    function_syntax
    generic
    hash
    hero
    init
    iterator
    join
    lambda
    lexer
    list_to_array
    m3ugen
    main
    member
    member_fun_pointer
    misc
    move
    mutable
    namespace
    operator
    operator_new
    override
    persist
    pool
    printdir
    random
    rar_extract
    readfast_textscroll
    regex
    rename_files
    replace
    rvalue
    set
    shared
    smart_pointer
    sort
    sort_files
    static
    stopwatch
    stream_insert_iterators
    stringstream
    symbol_table
    templates
    test
    thread
    tilemap
    tokenize
    transfer
    trim_lines
    try
    tuple
    typeid
    UNIX
    unordered_map
    variadic
    vector
)

set(EXAMPLE_SOURCES)
set(SKIP_SOURCES
    random/shuffle.cc
    random/shuffle2.cc
)

if(NOT BUILD_LEGACY_SDL1_DEMOS)
    list(APPEND SKIP_SOURCES
        tilemap/newtilemap/newtilemap/newtilemap/sdltest/test.cpp
    )
endif()
foreach(root IN LISTS EXAMPLE_ROOTS)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${root}")
        file(GLOB_RECURSE root_sources CONFIGURE_DEPENDS
            RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
            "${root}/*.cpp"
            "${root}/*.cc"
        )
        list(APPEND EXAMPLE_SOURCES ${root_sources})
    endif()
endforeach()

if(NOT SDL2_FOUND)
    set(SDL_SOURCES_TO_SKIP)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_sdl("${source_file}" has_sdl_include)
        string(TOLOWER "${source_file}" source_file_lower)
        if(has_sdl_include OR source_file_lower MATCHES "(^|/)(sdl|sdl2|tilemap)(/|$)")
            list(APPEND SDL_SOURCES_TO_SKIP "${source_file}")
        endif()
    endforeach()
    if(SDL_SOURCES_TO_SKIP)
        list(APPEND SKIP_SOURCES ${SDL_SOURCES_TO_SKIP})
    endif()
    message(STATUS "SDL2 package not found: skipping SDL-dependent example sources")
else()
    message(STATUS "SDL2 package found: building SDL-dependent example sources")
endif()

list(REMOVE_ITEM EXAMPLE_SOURCES
    ${SKIP_SOURCES}
    UNIX/shared/simple_lib/lib.cpp
    UNIX/shared/simple_lib/prog.cpp
    UNIX/shared/simple_lib2/lib.cpp
    UNIX/shared/simple_lib2/prog.cpp
    UNIX/shared/dynamic_load/lib.cpp
    UNIX/shared/dynamic_load/prog.cpp
    UNIX/shared/dynamic_init/lib.cpp
    UNIX/shared/dynamic_init/prog.cpp
)

set(EXAMPLE_DIRS)
foreach(source_file IN LISTS EXAMPLE_SOURCES)
    get_filename_component(source_dir "${source_file}" DIRECTORY)
    list(APPEND EXAMPLE_DIRS "${source_dir}")
endforeach()
list(REMOVE_DUPLICATES EXAMPLE_DIRS)

foreach(source_dir IN LISTS EXAMPLE_DIRS)
    file(GLOB dir_sources CONFIGURE_DEPENDS
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${source_dir}/*.cpp"
        "${source_dir}/*.cc"
    )
    list(REMOVE_ITEM dir_sources ${SKIP_SOURCES})

    set(main_sources)
    set(non_main_sources)
    foreach(source_file IN LISTS dir_sources)
        file_has_main("${source_file}" is_main)
        if(is_main)
            list(APPEND main_sources "${source_file}")
        else()
            list(APPEND non_main_sources "${source_file}")
        endif()
    endforeach()

    list(LENGTH main_sources main_count)

    if(main_count EQUAL 1)
        list(GET main_sources 0 main_source)
        make_target_name("${main_source}" target_name)
        add_executable(${target_name} ${dir_sources})
        link_unix_libs_if_needed(${target_name} "${main_source}")
        link_sdl2_if_needed(${target_name} ${dir_sources})
    elseif(main_count GREATER 1)
        foreach(main_source IN LISTS main_sources)
            make_target_name("${main_source}" target_name)
            add_executable(${target_name} "${main_source}" ${non_main_sources})
            link_unix_libs_if_needed(${target_name} "${main_source}")
            link_sdl2_if_needed(${target_name} "${main_source}" ${non_main_sources})
        endforeach()
    endif()
endforeach()

foreach(top_level_source IN ITEMS karma.cpp thought.cc)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${top_level_source}")
        file_has_main("${top_level_source}" is_main)
        if(is_main)
            make_target_name("${top_level_source}" target_name)
            add_executable(${target_name} "${top_level_source}")
        endif()
    endif()
endforeach()

add_unix_shared_example(simple_lib TRUE)
add_unix_shared_example(simple_lib2 TRUE)
add_unix_shared_example(dynamic_load FALSE)
add_unix_shared_example(dynamic_init FALSE)