#include <Devuino.hpp>

/* Constructor signature */
// Potentiometer(AnalogBackend&& pin, bool debounce = false, uint8_t iterations = 10)

/* Instantiate the device specific hardware interface */
ArduinoUno cpu {};

/* Instantiate a Potentiometer */
Potentiometer potentiometer {cpu.analog.input(0)};

void setup()
{
	/* Read value of potentiometer */
	const auto value = potentiometer;

	/* Read the value of the potentiometer in range [0..1] */
	const auto fraction = potentiometer.fraction();
}

void loop() { }