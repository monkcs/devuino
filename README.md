# /dev/uino
A standard device library for Arduino and other -ino's

It's a mess here right now, but work is going on!  
The goal with ths project is to create a clean and well-coded library for all kinds of devices attachable to Arduinos.
By utilizing modern C++ to create an efficient and high-level abstraction compared to vanilla arduino functions.


Help is always wanted! Especially the i/o (SPI, I2C) but of course other areas as well!


![xkcd standards comic](https://imgs.xkcd.com/comics/standards.png) xkcd
___

## Example code
This is a example program where a pushbutton and the on-circutboard led (number 13) are used. When the button is pressed the led light up.

The button is connected between arduino pin 3 and ground (because then the built-in pullup resistor can be used) and initiated by creating a `Button` object with a `Onboard` pin (that is a pin onboard the Arduino board) set to use pin number 3. In the loop `button.value()` reads the boolean value if the button is pressed or not.

```cpp
#include <devuino.h>

Button<Onboard> button(Onboard(3), Resistor::PullUp);
Led<Onboard>    led(Onboard(13));

void setup() { }

void loop()
{
    led.set(button.value());
}
```


## Device list

The devices that are currently supported, planned or not planned to be implemented.

🔵  *Implemented*  
⚫️  *Not implemented but planned*  
🔴  *Not planned*

### Basic

| Status | Device            | Description                                 |
| :----: | :---------------- | :------------------------------------------ |
| 🔵      | **Switch**        | Digital output to switch between on and off |
| 🔵      | **Button**        | Digital input between on and off            |
| 🔵      | **Potentiometer** | Analog input in bitsize range               |
| 🔵      | **Resistance** | Potentiometer with a autoremoved measuring current   |


### Mechanical

| Status | Mechanical | Description           |
| :----: | :--------- | :-------------------- |
| ⚫️     | **Servo**  | Control generic servo |


### Light
Light devices include both analog and digital controlled light sources.

| Status | Light        | Description                                 |
| :----: | :----------- | :------------------------------------------ |
| 🔵      | **Led**      | Light control on/off and brightness for led |
| 🔵      | **LedRgb**   | Same as Led but with 3-pin rgb              |
| 🔵      | **LedRgbw**  | Same as Led but with 4-pin rgbw             |
| ⚫️     | **Neopixel** | Neopixel/WS2812 1-wire rgb/rgbw led         |


### Sound
Sound devices include both buzzers to speakers and other primary sound-making devices.

| Status | Sound             | Description    |
| :----: | :---------------- | :------------- |
| ⚫️     | **BuzzerPassive** | Passive buzzer |
| ⚫️     | **BuzzerActive**  | Active buzzer  |


### Messuarement

| Status | Messuarement | Description             |
| :----: | :----------- | :---------------------- |
| 🔵     | **HCSR04**   | HC-SR04 distance sensor |


### Display

| Status | Display     | Description                         |
| :----: | :---------- | :---------------------------------- |
| ⚫️     | **Max72xx** | Max 7219/7221 seven-segment display |
