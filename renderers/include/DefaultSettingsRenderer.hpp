#pragma once
#include "Settings.hpp"
#include "SettingsRenderer.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

class DefaultSettingsRenderer : public SettingsRenderer {
public:
    virtual bool render(Settings &settings) override;
};
