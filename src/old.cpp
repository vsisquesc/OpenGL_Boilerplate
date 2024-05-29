#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)
#define W 640
#define H 480
#define C 3

bool load_frame( int* width ,int* height, int* channels, unsigned char ** data ){
    *width = W;
    *height = H;
    *channels = C;
    *data = new unsigned char[ *width * *height * *channels];

    auto ptr = *data;
    for(int x = 0; x < *width; ++x){
        for(int y = 0; y < *height; ++y){
            *ptr++ = 0xff;
            *ptr++ = 0x00;
            *ptr++ = 0x00;
        }
    }
    return true;
}

int main(){
  


    if(!glfwInit()){
        std::cerr << "Couldn't init GLFW" << std::endl;
        return 1;
    }

    GLFWwindow* window  = glfwCreateWindow(W, H, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);

    
    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) {
         std::cerr <<"Failed to initialize Glad context\n" << std::endl;
        return  1;
    }

    // Successfully loaded OpenGL
    std::cout << "Loaded OpenGL" << GLAD_VERSION_MAJOR(version) << GLAD_VERSION_MINOR(version) << std::endl;


    if(!window){
        std::cerr << "Couldn't open Window" << std::endl;
        return 1;
    }
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    int frame_width;
    int frame_height;
    int frame_channels;
    unsigned char* frame_data;



    GLuint texture_handle;
    {
        // SetUp FrameBuffer
        glGenTextures(1, &texture_handle);
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    
    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

        // Set up orthographic projection
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0 /*LEFT*/, window_width /*RIGHT*/, 0 /*BOTTOM*/, window_height /*TOP*/, -1  /*Z NEAR*/, 1  /*Z FAR*/);
        glMatrixMode(GL_MODELVIEW);


        // Gen Frame
        if(!load_frame(&frame_width, &frame_height, &frame_channels, &frame_data)){
            std::cerr << "No se puede cargar el frame";
            return 1;
        };
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame_data);
        // Render frame
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glBegin(GL_QUADS);
        // UV mapping de la textura al mundo; 
            glTexCoord2d(0,0); glVertex2i(0,           0);
            glTexCoord2d(1,0); glVertex2i(frame_width, 0);
            glTexCoord2d(1,1); glVertex2i(frame_width, frame_height);
            glTexCoord2d(0,1); glVertex2i(0,           frame_height);
        glEnd();
        glDisable(GL_TEXTURE_2D);






        glfwSwapBuffers(window); 
        glfwWaitEvents();
    }


    return 0;
}