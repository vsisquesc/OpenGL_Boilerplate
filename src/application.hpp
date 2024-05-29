#pragma once

#include "imgui.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// @TODO hacer una clase
namespace AppSkeleton {

void RenderUI(ImGuiIO io);
void _DockSpace();
bool load_frame( int width ,int height, unsigned char ** data );
bool loadTexture( int w, int h,   GLuint* out_texture);

void resetValues();

static int viewport_w = 100;
static int viewport_h = 100;
static float R = 1.0;
static float G = 1.0;
static float B = 1.0;
static float A = 1.0;

} // namespace AppSkeleton