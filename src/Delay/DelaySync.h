#pragma once

#include <Arduino.h>

namespace devuino
{
	[[maybe_unused]] static void DelaySync(const uint32_t milliseconds)
	{
		delay(milliseconds);
	};
}