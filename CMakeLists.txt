#GLExtension CMakesLists.txt
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
project(GLExtension VERSION 0.0.0)



message(STATUS "include path : ${PROJECT_SOURCE_DIR}/include")

#if(EXISTS ${LIB_PATH})
#else()
#message(STATUS "failed found LIB_PATH, it should be LIB_PATH :: Current Dir/lib")
#let the Root make a lib path
set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
#endif()
set(INC_PATH ${CMAKE_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC 
        ./include/GLExtension.h     
        ./include/GLExtension.cpp)

#add an alias
add_library(lib::GLExtension ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_PATH})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIB_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_PATH}
)

option(BUILD_EXAMPLES "Build Example" ON)

if(BUILD_EXAMPLES)
    message(STATUS "Build Examples...")
    add_subdirectory(Examples)
endif()

