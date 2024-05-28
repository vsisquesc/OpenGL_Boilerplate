cmake_minimum_required(VERSION 3.14)
project(OpenGL_Boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    list( APPEND EXTRA_LIBS "-framework OpenGl")
elseif(WIN32)
    list( APPEND EXTRA_LIBS "-lglu32 -lopengl32")
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list( APPEND EXTRA_LIBS "-lGl -lGLU -lX11")
endif()

add_subdirectory(lib/glfw)

list(APPEND SOURCES
    src/main.cpp
    src/load_frame.cpp)
add_executable(OpenGL_Boilerplate ${SOURCES})

target_link_libraries(OpenGL_Boilerplate glfw ${EXTRA_LIBS})