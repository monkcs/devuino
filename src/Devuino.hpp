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

// Include pins
#include "Pin/Onboard.hpp"

// Include devices
#include "Device/Button/Button.hpp"
#include "Device/HCSR04/HCSR04.hpp"
#include "Device/Led/Led.hpp"
#include "Device/Led/LedRgb.h"
#include "Device/Potentiometer/Potentiometer.hpp"
#include "Device/Resistance/Resistance.hpp"
// #include "Device/Servo/Servo.h"

//#include "Device/MAX7219/MAX7219.h"
#include "Device/Switch/Switch.hpp"

//#include "Display/Display.h"
//#include "Display/CharacterDisplay/SegmentDisplay/SegmentDisplay.h"
//#include "Device/Neopixel/Neopixel.h"

// Include Tools
#include "Light/Colour.hpp"

// Include I/O interfaces
#include "Interface/SPI.h"

// Put all namespaces into scope
using namespace devuino;
using namespace devuino::pin;
using namespace devuino::device;
using namespace devuino::interface::spi;
