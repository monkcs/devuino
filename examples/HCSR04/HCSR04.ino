#include <Devuino.hpp>

/* Constructor signature */
// HCSR04(Trigger&& trigger, Echo&& echo, bool debounce = false, Lenght minimum = 2_centimetre, Lenght maximum = 4_metre)

/* Instantiate the device specific hardware interface */
ArduinoUno cpu {};

/* Instantiate a HCSR04 ultrasound distance sensor */
HCSR04 sensor {cpu.digital.output(5), cpu.digital.input(6)};

void setup()
{
	/* Read the distance of the sensor */
	const Lenght lenght = sensor;

	/* Or like this */
	const auto distance = sensor.distance();
}

void loop() { }