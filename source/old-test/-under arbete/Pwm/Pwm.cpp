#include "Pwm.h"

void Pwm::off() {
	active = false;
	digitalWrite(pin, LOW);
}
