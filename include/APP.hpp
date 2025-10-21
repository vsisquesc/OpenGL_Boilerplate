#pragma once
#include "Settings.hpp"
#include "SettingsRenderer.hpp"
#include "ViewportRenderer.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>
#include <memory>

#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)
#define W 640
#define H 480
#define C 4

typedef std::function<bool(Settings &settings, unsigned char **data)> RenderFrameFunc;
typedef std::function<bool(Settings &settings)> RenderSettingsFunc;

class APP {
public:
    APP(Settings &app_settings);
    APP(Settings &app_settings, std::unique_ptr<ViewportRenderer> viewport, std::unique_ptr<SettingsRenderer> settings);
    int run();

private:
    GLuint texture_handler = 0;
    bool isResized = true;
    Settings &app_settings;
    std::unique_ptr<ViewportRenderer> _viewportRenderer;
    std::unique_ptr<SettingsRenderer> _settingsRenderer;

private:
    bool _loadTexture(int w, int h);
    bool _renderFrame_default(int w, int h, unsigned char **data);
    void _renderViewPort(ImGuiIO io);
    void _renderSettings(ImGuiIO io);
    void _dockSpace();
    void _resetValues();
};
