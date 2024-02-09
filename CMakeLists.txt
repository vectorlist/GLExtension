#GLExtension CMakesLists.txt
cmake_minimum_required(VERSION 3.14)

project(GLExtension VERSION 0.0.0)

message(STATUS "include path : ${PROJECT_SOURCE_DIR}/include")

set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} STATIC 
        ./include/GLExtension.h     
        ./include/GLExtension.cpp)

#add an alias
add_library(lib::GLExtension ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIB_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_PATH}
)

