#include <Devuino.hpp>

void setup()
{
	/* Constructor signature */
	// Switch(DigitalBackend&& pin, bool initial = false)

	/* Instantiate the device specific hardware interface */
	ArduinoUno cpu {};

	/* Instantiate a switch */
	Switch output {cpu.digital.output(3)};

	/* Assign a boolean value to the switch */
	output = true;

	/* Turn switch on or off */
	output.on();
	output.off();

	/* Toggle the current value of the switch */
	output.toggle();

	/* Get the current value of the switch */
	const bool value = output;
}

void loop() { }