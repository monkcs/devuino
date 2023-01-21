#include <Devuino.hpp>

/* Constructor signature */
// Button(DigitalBackend&& pin, Resistor pull = Resistor::None, bool debounce = false)

/* Instantiate the device specific hardware interface */
ArduinoUno cpu {};

/* Instantiate a button connected between pin 3 and ground.
   By using the internal pull-up resistor no external resistor is needed */
Button button {cpu.digital.input(3), Resistor::PullUp};

/* Instantiate the built-in led on the Arduino Uno board */
Light led {cpu.digital.output(13)};

void setup()
{
	/* Read the value from the button to a bool, returns true if it pressed */
	const bool reading = button;
}

void loop()
{
	/* Assign the value of the button to the led */
	led = button;
}