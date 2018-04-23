#include "Output.h"

void Output::toggle() {
	if (active = !active) {
		on();
	}
	else {
		off();
	}
}
