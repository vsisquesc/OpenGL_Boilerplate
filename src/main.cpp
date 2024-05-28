#include <iostream>
#include <GLFW/glfw3.h>


int main(){
    GLFWwindow* window;


    if(!glfwInit()){
        std::cerr << "Couldn't init GLFW" << std::endl;
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if(!window){
        std::cerr << "Couldn't open Window" << std::endl;
        return 1;
    }


    unsigned char* buffer_data = new unsigned char[100 * 100 * 3];
    for(int y =0; y < 100; y++){ 
        for(int x =0; x < 100; x++){
            uint16_t pixel_idx = y * 100*3 +x*3;
            buffer_data[pixel_idx + 0] = 0xff;
            buffer_data[pixel_idx + 1] = 0x00;
            buffer_data[pixel_idx + 2] = 0x00;
        }
    }

    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
        glDrawPixels(100, 100 ,GL_RGB, GL_UNSIGNED_BYTE , buffer_data);

        glfwSwapBuffers(window); 
        glfwWaitEvents();
    }


    return 0;
}