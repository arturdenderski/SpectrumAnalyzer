cmake_minimum_required(VERSION 3.0.0)
project(SpectrumAnalyzer VERSION 0.1.0)

set(SOURCE_FILES 
    include/app.h
    include/dataprocess.h
    include/visualizer.h
    src/app.cpp
    src/dataprocess.cpp
    src/visualizer.cpp
    src/main.cpp)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SpectrumAnalyzer ${SOURCE_FILES})

target_link_libraries(SpectrumAnalyzer ${SDL2_LIBRARIES})