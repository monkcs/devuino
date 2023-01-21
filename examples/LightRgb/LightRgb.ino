#include <Devuino.hpp>

/* Constructor signature */
// LightRgb(AnalogBackend&& redpin, AnalogBackend&& greenpin, AnalogBackend&& bluepin, Colour colours = Colour {}, bool initial = false)

void setup()
{
	/* Instantiate the device specific hardware interface */
	ArduinoUno cpu {};

	/* Instantiate a rgb light */
	LightRgb rgb {cpu.analog.output(1), cpu.analog.output(2), cpu.analog.output(3)};

	/* Turn light on or off */
	rgb = false;
	rgb.on();
	rgb.off();

	/* Toggle the current value of the light */
	rgb.toggle();

	/* Set brightness of light */
	rgb.brightness(255);
	rgb.fraction(0.2);

	/* Access individual channel */
	rgb.red.brightness(255);

	/* Set color */
	const Colour lilac = 0x9966cc;
	rgb = lilac;

	const Colour green = {0, 255, 0};
	rgb = green;
}

void loop() { }