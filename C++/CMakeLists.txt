cmake_minimum_required(VERSION 3.28)
project(demo)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Users/Chlzhong/Downloads/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML FOUND!")
endif()

include_directories(C:/Users/Chlzhong/Downloads/SFML-2.6.1})
add_executable(demo main.cpp)
target_link_libraries(demo sfml-audio sfml-network sfml-graphics sfml-window sfml-system)