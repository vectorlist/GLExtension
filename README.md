# GLExtension

OpenGL 4.6 for Win32

* External using
```cmake
add_subdirectory(GLExtension)
add_dependecy(<your project> lib::GLExtension)

target_include_directory(<your project> PUBLIC GLExtension/include)
target_link_directory(<your project> ${CMAKE_SOURCE_DIR}/lib)
```
