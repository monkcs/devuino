#include "Light.h"

byte Light::brightness() {
    return bright;
}
void Light::brightness(float percent) {
    brightness((byte)(255 * percent));
}