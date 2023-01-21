#include <Devuino.hpp>

/* Constructor signature */
// Light(AnalogBackend&& pin, bool initial = false, decltype(pin.bitsize.maximum) brightness = pin.bitsize.maximum)

void setup()
{
	/* Instantiate the device specific hardware interface */
	ArduinoUno cpu {};

	/* Instantiate a light */
	Light led {cpu.analog.output(1)};

	/* Turn light on or off */
	led = false;
	led.on();
	led.off();

	/* Toggle the current value of the light */
	led.toggle();

	/* Set brightness of light */
	led.brightness(500);
	led.fraction(0.7);

	/* Get brightness of light */
	const auto brightness = led.brightness();

	/* Increment and decrement brightness */
	led += 100;
	led -= 100;

	/* Read status of light, false if brightness is zero or the light is off */
	const bool value = led;
}

void loop()
{
	/* Assign the value of the button to the led */
	led = button;
}