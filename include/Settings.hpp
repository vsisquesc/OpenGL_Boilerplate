#pragma once
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

class Settings {
public:
    Settings();
    virtual void resetValues();
};
