#include "SettingsRenderer.hpp"
#include "Settings.hpp"
#include "ViewportSettings.hpp"

SettingsRenderer::SettingsRenderer(ViewportSettings &viewport_settings, Settings &local_settings) : viewport_settings(viewport_settings),
                                                                                                    local_settings(local_settings) {}