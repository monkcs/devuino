#pragma once

/*

   —— /dev/uino —————————————————————————————————————————————————————————
   Devuino (https://github.com/monkcs/devuino) created by Charlie Habolin

   The Devuino standard library aims to unify the library implementations
   for different devices to create clearer code and promote code reuse.

   If you want to write a device driver for the library, or just give a
   suggestion for a specific device, please open a issue on the Github
   project page.

   —— License ———————————————————————————————————————————————————————————
   All code, files or other assets in this project is licensed under the
   GNU Lesser General Public License v3.0.
   ——————————————————————————————————————————————————————————————————————

   —— This file —————————————————————————————————————————————————————————
   To make it easier to use this library by the everyday user, this file
   contains #import's and namespace import to put all the different parts
   into scope.
   ——————————————————————————————————————————————————————————————————————

*/

/* Include onboard pins */
#include "Onboard/Analog.hpp"
#include "Onboard/Digital.hpp"
#include "Onboard/Matrix.hpp"
#include "Onboard/Pin.hpp"

/* Include devices */
#include "Device/Button/Button.hpp"
#include "Device/HCSR04/HCSR04.hpp"
#include "Device/Light/Light.hpp"
#include "Device/Light/LightRgb.hpp"
#include "Device/MAX7219/MAX7219.hpp"
#include "Device/Potentiometer/Potentiometer.hpp"
#include "Device/Resistance/Resistance.hpp"
#include "Device/Switch/Switch.hpp"

/* Include Tools */
#include "Utilities/Array/Array.hpp"
#include "Utilities/Display/SegmentDisplay/SevenSegmentCharacter.hpp"
#include "Utilities/Display/SegmentDisplay/SevenSegmentString.hpp"
#include "Utilities/Lenght/Lenght.hpp"
#include "Utilities/Light/Colour.hpp"
#include "Utilities/Light/Spectrum.hpp"
#include "Utilities/Resolution/Resolution.hpp"
#include "Utilities/Span/Span.hpp"
#include "Utilities/String/String.hpp"
#include "Utilities/String/Stringview.hpp"
#include "Utilities/Temperature/Temperature.hpp"

/* Include I/O interfaces */
#include "Onboard/SPI.hpp"

/* Put all namspaces in scope */
using namespace devuino;
using namespace devuino::pin;
using namespace devuino::onboard;
using namespace devuino::device;
using namespace devuino::utilities;
using namespace devuino::onboard::spi;