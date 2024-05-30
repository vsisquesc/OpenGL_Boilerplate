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

class APP_settings {
public:
    void resetValues();

    int viewport_w = 100;
    int viewport_h = 100;
    float scale = 1.0;
    float R = 1.0;
    float G = 1.0;
    float B = 1.0;
    float A = 1.0;
};
