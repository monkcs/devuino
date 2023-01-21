#include <Devuino.hpp>

/* Constructor signature */
// Resistance(Potentiometer<Signal>&& signal, Switch<Power>&& power)

/* Instantiate the device specific hardware interface */
ArduinoUno cpu {};

/* Instantiate a Potentiometer */
Resistance sensor {Potentiometer {cpu.analog.input(0)}, Switch {cpu.digital.output(2)}};

void setup()
{
	/* Read value of sensor */
	const auto value = sensor;

	/* Read the value of the sensor in range [0..1] */
	const auto fraction = sensor.fraction();
}

void loop() { }