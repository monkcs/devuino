#pragma once

/*

   —— Devuino ———————————————————————————————————————————————————————————
   Devuino (https://github.com/monkcs/devuino) created by Charlie Habolin

   The Devuino standard library aims to unify the library implementations
   for different devices to make clearer code and promote code reuse.

   If you want to write or add a device to the library, or just give a
   suggestion for a specific device, open a issue on the git project page.


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

//#pragma GCC optimize("O3")
//#pragma GCC reset_options

// Include pins
#include "Pin/Matrix.hpp"
#include "Pin/Onboard.hpp"

// Include devices
#include "Device/Button/Button.hpp"
#include "Device/HCSR04/HCSR04.hpp"
#include "Device/Light/Light.hpp"
#include "Device/Light/LightRgb.hpp"
#include "Device/Potentiometer/Potentiometer.hpp"
#include "Device/Resistance/Resistance.hpp"
// #include "Device/Servo/Servo.h"

//#include "Device/MAX7219/MAX7219.hpp"
#include "Device/Switch/Switch.hpp"

//#include "Display/Display.h"
#include "Display/CharacterDisplay/SegmentDisplay/SevenSegmentString.hpp"
//#include "Device/Neopixel/Neopixel.h"
#include "Temperature/Temperature.hpp"
// Include Tools
#include "Distance/Distance.hpp"
#include "Light/Colour.hpp"
#include "Tools/Array.hpp"
#include "Tools/Span.hpp"
#include "Tools/String.hpp"
#include "Tools/Stringview.hpp"

// Include I/O interfaces
//#include "Interface/SPI.h"

// Put all namespaces into scope
using namespace devuino;
using namespace devuino::tools;
using namespace devuino::pin;
using namespace devuino::device;
// using namespace devuino::interface::spi;