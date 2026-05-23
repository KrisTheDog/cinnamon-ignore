cmake_minimum_required(VERSION 3.21)
project(n3ds_preprocess C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

add_executable(n3ds-preprocess
    main.c
    stb_impl.c
    ../../src/binary_reader.c
    ../../src/data_win.c
    ../../src/gl/image_decoder.c
)

target_include_directories(n3ds-preprocess PRIVATE
    ../../src
    ../../vendor
    ../../vendor/stb/ds
    ../../vendor/stb/image
)

target_compile_definitions(n3ds-preprocess PRIVATE IMAGE_DECODER_HAS_BZ2=0)
