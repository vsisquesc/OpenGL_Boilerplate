#pragma once
#include "Settings.hpp"
#include "ViewportRenderer.hpp"
#include "ViewportSettings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

class DefaultViewportRenderer : public ViewportRenderer {
public:
    DefaultViewportRenderer(ViewportSettings &viewport_settings, Settings &settings);
    virtual bool render(unsigned char **data) override;
};
