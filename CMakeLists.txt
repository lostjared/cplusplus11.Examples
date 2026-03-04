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

find_package(Threads REQUIRED)
find_library(CRYPT_LIBRARY crypt)
find_path(SDL_INCLUDE_DIR
    NAMES SDL.h SDL2/SDL.h
    PATH_SUFFIXES SDL2 SDL
)

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

if(NOT SDL_INCLUDE_DIR)
    set(SDL_SOURCES_TO_SKIP)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}" source_content)
        string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*SDL[^>\"]*[>\"]" has_sdl_include "${source_content}")
        string(TOLOWER "${source_file}" source_file_lower)
        if(has_sdl_include OR source_file_lower MATCHES "(^|/)(sdl|sdl2|tilemap)(/|$)")
            list(APPEND SDL_SOURCES_TO_SKIP "${source_file}")
        endif()
    endforeach()
    if(SDL_SOURCES_TO_SKIP)
        list(APPEND SKIP_SOURCES ${SDL_SOURCES_TO_SKIP})
    endif()
    message(STATUS "SDL headers not found: skipping SDL-dependent example sources")
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
    elseif(main_count GREATER 1)
        foreach(main_source IN LISTS main_sources)
            make_target_name("${main_source}" target_name)
            add_executable(${target_name} "${main_source}" ${non_main_sources})
            link_unix_libs_if_needed(${target_name} "${main_source}")
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