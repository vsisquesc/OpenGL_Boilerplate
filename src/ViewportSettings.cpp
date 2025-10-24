#include "ViewportSettings.hpp"

ViewportSettings::ViewportSettings() {
    this->viewport_w = 100;
    this->viewport_h = 100;
    this->scale = 1.0;
    this->R = 1.0;
    this->G = 1.0;
    this->B = 1.0;
    this->A = 1.0;
}

void ViewportSettings::resetValues() {
    *this = ViewportSettings();
}
