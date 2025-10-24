#pragma once
#include "Settings.hpp"
#include "ViewportSettings.hpp"

class SettingsRenderer {
public:
    SettingsRenderer(ViewportSettings &viewport_settings, Settings &local_settings);
    virtual bool render() = 0;

protected:
    ViewportSettings &viewport_settings;
    Settings &local_settings;
};
