#include <Devuino.hpp>

/* Instantiate the device specific hardware interface */
ArduinoUno cpu {};

/* Instantiate the spi controller */
auto spi = cpu.spi();

/* Instantiate the display using the chip select pin 10.
   The display is by default turend on displaying nothing. */
MAX7219 display {spi.controller(cpu.digital.output(10))};

void setup()
{
	/* The display has a test mode, powerering on all segments */
	// display.test(true);

	/* The display can be turned off and on, or assigned a bool, or toggled */
	display.off();
	display.on();
	display.set(false);
	display.toggle();

	/* Brightness can be set from 0 to 15. Or a fraction 0.0 to 1.0 */
	display.brightness(15);
	display.fraction(0.5);

	/* Brightness can be read */
	const auto brightness = display.brightness();

	/* The display can be cleared */
	display.clear();

	/* To print a string, assign it to the display */
	display = "12345";		 // Raw char array
	display = "12345"_sv;	 // Stringview

	/* Recommended for static strings, smaller code size */
	display = "12345"_max7219;	  // Device specific constexpr SevenSegmentString
}

void loop() { }