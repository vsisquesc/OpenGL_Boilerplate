#pragma once
#include "DefaultViewportRenderer.hpp"
#include "APP.hpp"
#include "Settings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

bool DefaultViewportRenderer::render(Settings &settings, unsigned char **data) {

    int w = settings.viewport_w;
    int h = settings.viewport_h;
    // Gestionar cambios en h y w; hacer estático
    *data = new unsigned char[w * h * C];

    //  Hacer dinámico
    float c_values[C] = {
        settings.R,
        settings.G,
        settings.B,
        settings.A};
    auto ptr = *data;
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            for (int z = 0; z < C; z++) {
                int idx = (y * w * C) + (x * C) + z;
                ptr[idx] = 0xaa * c_values[z];
            }
        }
    }
    return true;
}
