#include <Devuino.hpp>

void setup()
{
	/* Instantiate the device specific hardware interface */
	ArduinoUno cpu {};

	auto eeprom = cpu.eeprom();
	auto raw = eeprom.raw();

	/* Access a byte in eeprom memory */
	raw[100] = 123;

	/* Assignment will only write if value is different to minimize write wear */
	raw[100] = 123;

	/* Set all bytes to zero */
	raw.erase();

	/* Set all bytes to 111 */
	raw.fill(111);

	for (auto cell : raw)
	{
		cell = 223;
	}

	/* Value of byte in eeprom memory can be read */
	auto cell = raw[500];
	const uint8_t reading = cell;
}

void loop() { }