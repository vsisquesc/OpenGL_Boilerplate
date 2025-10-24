#include "ViewportRenderer.hpp"
#include "Settings.hpp"
#include "ViewportSettings.hpp"

ViewportRenderer::ViewportRenderer(ViewportSettings &viewport_settings, Settings &local_settings) : viewport_settings(viewport_settings),
                                                                                                    local_settings(local_settings) {}