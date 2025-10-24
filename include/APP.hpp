#pragma once
#include "Settings.hpp"
#include "SettingsRenderer.hpp"
#include "ViewportRenderer.hpp"
#include "ViewportSettings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>
#include <memory>

#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)
#define W 640
#define H 480
#define C 4

class APP {
public:
    APP(ViewportSettings &viewport_settings, Settings &local_settings);
    APP(ViewportSettings &viewport_settings, Settings &local_settings, std::unique_ptr<ViewportRenderer> viewport, std::unique_ptr<SettingsRenderer> settings);
    int run();

private:
    GLuint texture_handler = 0;
    bool isResized = true;
    ViewportSettings &viewport_settings;
    Settings &local_settings;
    std::unique_ptr<ViewportRenderer> _viewportRenderer;
    std::unique_ptr<SettingsRenderer> _settingsRenderer;

private:
    bool _loadTexture(int w, int h);
    void _renderViewPort(ImGuiIO io);
    void _renderSettings(ImGuiIO io);
    void _dockSpace();
    void _resetValues();
};
