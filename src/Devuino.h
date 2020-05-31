

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

 #pragma interface

/* Include pins */
#include "Pin/Onboard.h"

/* Include devices */
#include "Device/Button/Button.h"
#include "Device/HCSR04/HCSR04.h"
#include "Device/Led/Led.h"
#include "Device/Led/LedRgb.h"
//#include "Device/Led/LedRgbw.h"
#include "Device/Potentiometer/Potentiometer.h"
#include "Device/Resistance/Resistance.h"
#include "Device/Servo/Servo.h"
#include "Device/Switch/Switch.h"
#include "Device/MAX7219/MAX7219.h"

#include "Display/Display.h"
#include "Display/CharacterDisplay/SegmentDisplay/SegmentDisplay.h"

/* Include Tools */
#include "Light/Colour.h"

/* Include I/O interfaces */
#include "Interface/SPI.h"

/* Put all namespaces into scope */
using namespace devuino;
using namespace devuino::pin;
using namespace devuino::device;
using namespace devuino::interface::spi;
