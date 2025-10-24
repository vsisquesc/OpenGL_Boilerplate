#pragma once
#include "Settings.hpp"
#include "ViewportSettings.hpp"

class ViewportRenderer {
public:
    virtual bool render(ViewportSettings &viewport_settings, Settings &local_settings, unsigned char **data) = 0;
};
