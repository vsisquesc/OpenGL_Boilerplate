#include "DefaultSettingsRenderer.hpp"
#include "APP.hpp"
#include "Settings.hpp"
#include "SettingsRenderer.hpp"
#include "ViewportSettings.hpp"
#include <functional>
#include <glad/glad.h>
#include <imgui.h>

DefaultSettingsRenderer::DefaultSettingsRenderer(ViewportSettings &viewport_settings, Settings &settings) : SettingsRenderer(viewport_settings, settings) {
}

bool DefaultSettingsRenderer::render() {

    return true;
}
