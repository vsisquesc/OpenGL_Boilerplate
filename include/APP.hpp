#pragma once
#include "APP_Settings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)
#define W 640
#define H 480
#define C 4

typedef std::function<bool()> RenderSettingsFunc;
typedef std::function<bool(APP_settings settings, unsigned char **data)> RenderFrameFunc;

class APP {
public:
    APP(RenderFrameFunc viewport, RenderSettingsFunc settings);
    int run();

private:
    GLuint texture_handler = 0;
    bool isResized = true;
    RenderFrameFunc _renderFrame_callback;
    RenderSettingsFunc _renderSettings_callback;
    APP_settings app_settings;

private:
    bool _loadTexture(int w, int h);
    bool _renderFrame_default(int w, int h, unsigned char **data);
    void _renderViewPort(ImGuiIO io);
    void _renderSettings(ImGuiIO io);
    void _dockSpace();
    void _resetValues();
};
