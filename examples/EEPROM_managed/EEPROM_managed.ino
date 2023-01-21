#include <Devuino.hpp>

struct Structure
{
	int integer;
	double floating;
};

void setup()
{
	/* Instantiate the device specific hardware interface */
	ArduinoUno cpu {};

	auto eeprom = cpu.eeprom();

	/* At construction a managed Structure will load data from eeprom.
	   The destructor will write changes to eeprom */
	auto storage = eeprom.managed<Structure>();

	/* Access members of Structure */
	storage->integer = -12345;

	/* Force write to eeprom */
	storage.save();
}

void loop() { }