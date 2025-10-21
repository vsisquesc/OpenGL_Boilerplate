#pragma once
#include "Settings.hpp"

class SettingsRenderer {
public:
    virtual bool render(Settings &settings) = 0;
};
