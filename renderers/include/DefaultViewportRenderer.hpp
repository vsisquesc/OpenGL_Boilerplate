#pragma once
#include "Settings.hpp"
#include "ViewportRenderer.hpp"
#include "ViewportSettings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

class DefaultViewportRenderer : public ViewportRenderer {
public:
    virtual bool render(ViewportSettings &viewport_settings, Settings &settings, unsigned char **data) override;
};
