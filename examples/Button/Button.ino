#include <Devuino.hpp>

/* Instantiate a button connected between pin 3 and ground.
   By using the internal pull-up resistor no external resistor is needed */
Button<> button {{3}, Resistor::PullUp};

/* Instantiate the built-in led on the arduino uno board */
Light<> led {{13}};

void setup()
{
	/* Read the value from the button to a bool, if it pressed or not */
	const bool reading = button;
}

void loop()
{
	/* Set the led to the value of the button */
	led = button;
}