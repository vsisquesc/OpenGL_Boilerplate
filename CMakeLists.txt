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
add_subdirectory(lib/glad)

# -------------- IMGUI static library creation`
#
set(IMGUI_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/imgui)
file(GLOB IMGUI_GLOB
    ${IMGUI_PATH}/imgui.h
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imconfig.h
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_internal.h
    ${IMGUI_PATH}/imstb_rectpack.h
    ${IMGUI_PATH}/imstb_textedit.h
    ${IMGUI_PATH}/imstb_truetype.h
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp

    # specific bindings...
    ${IMGUI_PATH}/backends/imgui_impl_glfw.h
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)
add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE glfw)
# ----------------------------------------------------------------------


list(APPEND SOURCES
    src/test.cpp )
# list(APPEND SOURCES
#     src/main.cpp
#     src/load_frame.cpp )
add_executable(OpenGL_Boilerplate ${SOURCES})

target_link_libraries(OpenGL_Boilerplate PUBLIC glfw glad imgui ${EXTRA_LIBS})
target_include_directories(OpenGL_Boilerplate PUBLIC glfw glad imgui ${EXTRA_LIBS})