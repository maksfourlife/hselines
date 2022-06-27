cmake_minimum_required(VERSION 3.19.6)

set(PROJECT_NAME hselines)
set(CMAKE_CXX_STANDARD 17)

project(
    ${PROJECT_NAME}
)

add_executable(
    ${PROJECT_NAME}
    src/main.cc
    src/App.cc
    src/Board.cc
    src/Count.cc
    src/ResourceManager.cc
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    /usr/local/include
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC
    /usr/local/lib
)

target_link_libraries(
    ${PROJECT_NAME}

    sfml-system-s
    sfml-window-s
    sfml-graphics-s

    freetype
)

if(APPLE)
    target_link_libraries(
        ${PROJECT_NAME}

        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework Carbon"
        "-framework IOKit"
        "-framework AppKit"
    
        -ObjC
    )
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
