#pragma once
#include "Settings.hpp"

class ViewportRenderer {
public:
    virtual bool render(Settings &settings, unsigned char **data) = 0;
};
