# /dev/uino

A device library for Arduino and other -ino's.

The goal with this project is to create a clean and well-coded library for all kinds of devices attachable to Arduinos. By utilizing modern C++ to create an efficient and high-level abstraction compared to vanilla arduino functions.

It's a mess here right now, but work is going on!  

Help is always wanted! If you want to write a device driver for the library, or just give a suggestion for a specific device, please open a issue.

![xkcd standards comic](https://imgs.xkcd.com/comics/standards.png) xkcd
___

## Example

Following example demonstrate on a ATmega328 (Arduino Uno), how to program the on-circutboard led (pin 13) to turn on when a push-button is pressed.

Two device objects are created, `Button` and `Light`.
The push-button is connected between pin 3 and ground, and uses the built-in pullup resistor. The light is connected to pin 13.

In the loop the reading of the current state of the button is assigned to the led.

```cpp
#include <devuino.hpp>

void setup()
{
    ATmega328 cpu;

    Button button {cpu.digital.input(3), Resistor::PullUp};
    Light led {cpu.analog.output(13)};

    while (true)
    {
        led = button;
    }
 }

void loop() { }
```

## Support

⚫️ = Not supported yet\
🔵 = Some support\
✅ = Fully supported

### Supported microcontrollers

Following microcontrollers are supported.

| Status | Device            | Implemented | Not implemented yet |
| :----: | :---------------- | :---------- | :---------- |
| 🔵     | **ATtiny25**      | Digital I/O, Analog I/O, Pin iterrupt, Pin change interrupt, EEPROM, SPI controller (via USI) | SPI device (via USI), I2C (via USI), USART (via USI), Low-power mode configuration
| 🔵     | **ATtiny45**      | Digital I/O, Analog I/O, Pin iterrupt, Pin change interrupt, EEPROM, SPI controller (via USI) | SPI device (via USI), I2C (via USI), USART (via USI), Low-power mode configuration
| 🔵     | **ATtiny85**      | Digital I/O, Analog I/O, Pin iterrupt, Pin change interrupt, EEPROM, SPI controller (via USI) | SPI device (via USI), I2C (via USI), USART (via USI), Low-power mode configuration
| 🔵     | **ATmega328**     | Digital I/O, Analog I/O, Pin iterrupt, Pin change interrupt, EEPROM, SPI controller | SPI device, I2C, USART, Low-power mode configuration |

### Supported devices

Following devices are supported.

| Status | Device | Description |
| :----: | :----- | :---------- |
| ✅     | **Switch** | Digital output between on and off |
| ✅     | **Button** | Digital input between on and off |
| ✅     | **Potentiometer** | Analog input in selectable range |
| ✅     | **Resistance** | Potentiometer with a auto-removed measuring voltage   |
| ✅     | **Light** | Analog output, supporting independent on/off and brightness control |
| ✅     | **LightRgb** | Same as Light but with 3 channels for rgb control |
| ⚫️     | **Neopixel** | Neopixel/WS2812 1-wire rgb/rgbw led |
| ✅     | **HCSR04**   | HC-SR04 distance sensor |
| ✅     | **MAX7219 segment display** | MAX7219 seven segment display |
| ⚫️     | **MAX7219 dotmatrix display** | MAX7219 dotmatrix display |

## Installation

To download the library, use the [Arduino IDE Library Manager](https://www.arduino.cc/reference/en/libraries/devuino/).

Note that the library requires at least C++17, so editing of the ```platform.txt``` file is required. The file, usually located at ```~/.arduino15/packages/arduino/hardware/avr/x.x.x/platform.txt``` should be changed on line ```compiler.cpp.flags``` to have the flag ```-std=gnu++17``` instead of the default one.
