# GLExtension

OpenGL 4.6 for Win32

* External using
```cmake
add_subdirectory(GLExtension)
add_dependecy(<your project> lib::GLExtension)

target_include_directory(<your project> PUBLIC GLExtension/include)
target_link_directory(<your project> ${CMAKE_SOURCE_DIR}/lib)
```

* cpp
``` c++
//Create
HWND hwnd = CreateWindowEx(NULL, ...,hInstance, 0);
HGLRC rc = GL::CreateGLContext(hwnd);
HDC dc = GetDC(hwnd);

//Release
GL::ReleaseContext(hwnd, rc, dc); 
```