cmake_minimum_required(VERSION 3.19.6)

set(CMAKE_CXX_STANDARD 17)

project(hselines)

# Приложение
add_executable(
    lines
    src/main.cc
    src/App.cc
    src/Board.cc
    src/Count.cc
    src/ResourceManager.cc
)

target_include_directories(
    lines
    PUBLIC
    /usr/local/include
)

target_link_directories(
    lines
    PUBLIC
    /usr/local/lib
)

target_link_libraries(
    lines

    sfml-system-s
    sfml-window-s
    sfml-graphics-s

    freetype
)

if(APPLE)
    target_link_libraries(
        lines

        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework Carbon"
        "-framework IOKit"
        "-framework AppKit"
    
        -ObjC
    )
endif()

add_custom_command(
    TARGET lines
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:lines>/assets
)

# Тесты
add_executable(
    tests
    tests/test_res.cc

    src/App.cc
    src/Board.cc
    src/Count.cc
    src/ResourceManager.cc
)

target_include_directories(
    tests
    PUBLIC
    /usr/local/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_directories(
    tests
    PUBLIC
    /usr/local/lib
)

target_link_libraries(
    tests

    sfml-system-s
    sfml-window-s
    sfml-graphics-s

    freetype
)

if(APPLE)
    target_link_libraries(
        tests

        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework Carbon"
        "-framework IOKit"
        "-framework AppKit"
    
        -ObjC
    )
endif()

add_custom_command(
    TARGET tests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:tests>/assets
)
