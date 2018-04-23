#include "OutputDigital.h"

void OutputDigital::toggle() {
	if ((active = !active)) {
		on();
	}
	else {
		off();
	}
}