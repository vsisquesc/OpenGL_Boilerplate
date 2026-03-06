
#include "imgui.h"
#include <iostream>

#include "APP.hpp"

// Main code
int main() {
    ViewportSettings viewport_settings = ViewportSettings();
    Settings local_settings = Settings();
    APP application = APP(viewport_settings, local_settings);
    application.run();
    return 0;
}