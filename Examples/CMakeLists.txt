#Examples

add_executable(win32 win32.cpp)

target_include_directories(win32 PUBLIC ${INC_PATH})
target_link_directories(win32 PUBLIC ${LIB_PATH})
target_link_libraries(win32 PUBLIC "GLExtension.lib")

set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set_target_properties(win32 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_PATH}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_PATH}
)