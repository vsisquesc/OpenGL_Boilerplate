#pragma once

#include "imgui.h"
#include <glad/glad.h>

// @TODO hacer una clase
namespace AppSkeleton {

void RenderUI(ImGuiIO io);
void _DockSpace();
bool load_frame(int width, int height, unsigned char **data);
bool loadTexture(int w, int h, GLuint *out_texture);

void resetValues();

static int viewport_w = 100;
static int viewport_w_min = 50;
static int viewport_w_max = 2000;
static int viewport_h = 100;
static int viewport_h_min = 50;
static int viewport_h_max = 2000;
static float scale = 1.0;
static float scale_min = 0.5;
static float scale_max = 4.0;
static float R = 1.0;
static float G = 1.0;
static float B = 1.0;
static float A = 1.0;

} // namespace AppSkeleton