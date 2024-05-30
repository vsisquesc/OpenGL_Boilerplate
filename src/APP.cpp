#include "APP.hpp"
#include "APP_Settings.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
APP::APP(RenderFrameFunc viewport, RenderSettingsFunc settings) {
    this->_renderFrame_callback = viewport;
    this->_renderSettings_callback = settings;
}

void APP::_renderViewPort(ImGuiIO io) {
    ImGui::Begin("Viewport");

    //  Renderizar imagen
    int w = this->app_settings.viewport_w;
    int h = this->app_settings.viewport_h;
    this->_loadTexture(w, h);

    float scaled_w = this->app_settings.scale * w;
    float scaled_h = this->app_settings.scale * h;

    ImGui::Text("pointer = %x", this->texture_handler);
    ImGui::Text("size = %d x %d", w, h);
    ImGui::Image((void *)(intptr_t)this->texture_handler, ImVec2(scaled_w, scaled_h), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));

    ImGui::End();
}
void APP::_renderSettings(ImGuiIO io) {

    ImGui::Begin("Settings");

    if (ImGui::CollapsingHeader("Basic options")) {

        if (ImGui::Button("Reset")) {
            this->_resetValues();
        }

        if (ImGui::InputInt("W", &this->app_settings.viewport_w)) {
            this->isResized = true;
            if (this->app_settings.viewport_w < VIEWPORT_W_MIN)
                this->app_settings.viewport_w = VIEWPORT_W_MIN;
            if (this->app_settings.viewport_w > VIEWPORT_W_MAX)
                this->app_settings.viewport_w = VIEWPORT_W_MAX;
        }

        if (ImGui::InputInt("H", &this->app_settings.viewport_h)) {
            this->isResized = true;
            if (this->app_settings.viewport_h < VIEWPORT_H_MIN)
                this->app_settings.viewport_h = VIEWPORT_H_MIN;
            if (this->app_settings.viewport_h > VIEWPORT_H_MAX)
                this->app_settings.viewport_h = VIEWPORT_H_MAX;
        }

        ImGui::SliderFloat("Scale", &this->app_settings.scale, SCALE_MIN, SCALE_MAX);
        ImGui::SliderFloat("R", &this->app_settings.R, 0.0f, 1.0f);
        ImGui::SliderFloat("G", &this->app_settings.G, 0.0f, 1.0f);
        ImGui::SliderFloat("B", &this->app_settings.B, 0.0f, 1.0f);
        ImGui::SliderFloat("A", &this->app_settings.A, 0.0f, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
    if (this->_renderSettings_callback != nullptr) {
        if (ImGui::CollapsingHeader("Custom options")) {
            this->_renderSettings_callback();
        }
    }
    ImGui::End();
}

void APP::_resetValues() {

    this->app_settings.resetValues();
    this->isResized = true;
}

// =================================================

void APP::_dockSpace() {

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin("DockSpace", nullptr, window_flags);

    ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

static void glfw_error_callback(int error, const char *description) {
    std::cerr << "GLFW Error" << error << ":" << description << std::endl;
}

int APP::run() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::cerr << "Couldn't init GLFW" << std::endl;
        return 1;
    }

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(W, H, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!window) {
        std::cerr << "Couldn't open Window" << std::endl;
        return 1;
    }

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) {
        std::cerr << "Failed to initialize Glad context\n"
                  << std::endl;
        return 1;
    }

    // Successfully loaded OpenGL
    std::cout << "Loaded OpenGL" << GLAD_VERSION_MAJOR(version) << GLAD_VERSION_MINOR(version) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    // Textura en la que se escribirá el framebuffer
    glGenTextures(1, &this->texture_handler);

    while (!glfwWindowShouldClose(window)) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // My code goes here!
        this->_dockSpace();
        this->_renderViewPort(io);
        this->_renderSettings(io);

        // Rendering
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// =================================================

// Simple helper function to load an image into a OpenGL texture with common settings
bool APP::_loadTexture(int w, int h) {
    unsigned char *frame_data;
    if (this->_renderFrame_callback != nullptr) {
        if (!this->_renderFrame_callback(this->app_settings, &frame_data)) {
            return false;
        }
    } else {
        if (!this->_renderFrame_default(w, h, &frame_data)) {
            return false;
        }
    }

    // Create a OpenGL texture identifier
    glBindTexture(GL_TEXTURE_2D, this->texture_handler);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    if (this->isResized) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);
        this->isResized = false;
    } else {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);
    }

    return true;
}

bool APP::_renderFrame_default(int w, int h, unsigned char **data) {
    // Gestionar cambios en h y w; hacer estático
    *data = new unsigned char[w * h * C];

    //  Hacer dinámico
    float c_values[C] = {
        this->app_settings.R,
        this->app_settings.G,
        this->app_settings.B,
        this->app_settings.A};
    auto ptr = *data;
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            for (int z = 0; z < C; z++) {
                int idx = (y * w * C) + (x * C) + z;
                ptr[idx] = 0xff;
            }
        }
    }
    return true;
}