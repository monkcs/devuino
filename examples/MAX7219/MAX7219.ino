#include <Devuino.hpp>

/* Instantiate the Spi port for communication to display */
Spi port {0};

/* Instantiate the display using the chip select pin 10.
   The display is by default turend on displaying nothing. */
MAX7219<Onboard> display {port.controller(Onboard {10})};

void setup()
{
	/* The display has a test mode, displaying all digits */
	// display.test(true);

	/* The display can be turned off and on, or assigned a bool, or toggled */
	display.off();
	display.on();
	display.set(false);
	display.toggle();

	/* Brightness can be set from 0 to 15. Or a fraction 0.0 to 1.0 */
	display.brightness(15);
	display.fraction(0.5);

	/* To print a string, assign it to the display */
	display = "12345";

	/* To print to a specific character use operator[]. Call print() to display changes */
	display[5] = '6';
	display[6] = '7';
	display[7] = '8';
	display.print();

	/* The display can be cleared */
	// display.clear();

	/* Remove return to run for-loop */
	return;
	/* Access every character on the display */
	for (auto& character : display)
	{
		character = '-';
	}

	display.print();
}

void loop() { }