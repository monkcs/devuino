#pragma once

#include <stdint.h>

namespace devuino::onboard
{
	class EepromBackend
	{
	  public:
		/* // May not be needed, if EECR is reset to zero on reset
			EepromBackend()
			{
				/ * Set Programming mode * /
				EECR = (0 << EEPM1) | (0 << EEPM0);
			}
		*/

		/// @brief Read the value at the current address
		uint8_t read(const uint16_t address) const
		{
			/* Wait for completion of previous write */
			while (EECR & (1 << EEPE)) { }

			EEAR = address;

			/* Start eeprom read by writing EERE */
			EECR |= (1 << EERE);

			return EEDR;
		}

		void write(const uint16_t address, const uint8_t data)
		{
			/* Wait for completion of previous write */
			while (EECR & (1 << EEPE)) { }

			EEAR = address;
			EEDR = data;

			/* Write logical one to EEMPE */
			EECR |= (1 << EEMPE);

			/* Start eeprom write by setting EEPE */
			EECR |= (1 << EEPE);
		}
	};
}
