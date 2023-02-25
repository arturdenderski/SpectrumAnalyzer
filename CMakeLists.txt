cmake_minimum_required(VERSION 3.0.0)
project(spectrum_analyzer VERSION 0.1.0)

set(SOURCE_FILES 
    include/app.h
    include/dataprocess.h
    include/visualizer.h
    src/app.cpp
    src/dataprocess.cpp
    src/visualizer.cpp
    src/main.cpp)

add_executable(spectrum_analyzer ${SOURCE_FILES})

target_include_directories(spectrum_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SDL-2.26.3/include)

target_link_libraries(spectrum_analyzer SDL2main SDL2)

if (WIN32)
    add_definitions(-DSDL_MAIN_HANDLED)
endif (WIN32)
