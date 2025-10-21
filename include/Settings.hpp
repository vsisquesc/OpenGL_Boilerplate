#pragma once
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

#define VIEWPORT_W_MIN 50
#define VIEWPORT_W_MAX 2000
#define VIEWPORT_H_MIN 50
#define VIEWPORT_H_MAX 2000
#define SCALE_MIN 0.5
#define SCALE_MAX 4.0

class Settings {
public:
    Settings();
    virtual void resetValues();

    int viewport_w;
    int viewport_h;
    float scale;
    float R;
    float G;
    float B;
    float A;
};
