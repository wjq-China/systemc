cmake_minimum_required(VERSION 3.10)
project(Adder)
 
set(CMAKE_CXX_STANDARD 17)
 
set(SYSTEMC_INLCUDE_DIRS "/home/hacker/Software/systemc/include/")
include_directories(${SYSTEMC_INLCUDE_DIRS})
file(GLOB_RECURSE SYSTEMC_LIB "/home/hacker/Software/systemc/lib-linux64/*.so")
 
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src) 
add_executable(${PROJECT_NAME} main.cpp ${src_sources})
target_link_libraries(${PROJECT_NAME} ${SYSTEMC_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${include_dir})