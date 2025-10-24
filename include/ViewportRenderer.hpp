#pragma once
#include "Settings.hpp"
#include "ViewportSettings.hpp"

class ViewportRenderer {
public:
    ViewportRenderer(ViewportSettings &viewport_settings, Settings &local_settings);
    virtual bool render(unsigned char **data) = 0;

protected:
    ViewportSettings &viewport_settings;
    Settings &local_settings;
};
