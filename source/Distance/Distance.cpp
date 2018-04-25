#include "Distance.h"

float Distance::decimetre() {
    return metre() * 10.0;
}

float Distance::centimetre() {
    return metre() * 100.0;
}

float Distance::millimetre() {
    return metre() * 1000.0;
}

float Distance::micrometre() {
    return metre() * 1000000.0;
}

float Distance::yard() {
    return metre() / 0.9144;
}

float Distance::foot() {
    return metre() / 0.3048;
}

float Distance::inch() {
    return metre() / 0.0254;
}
