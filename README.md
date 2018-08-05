# /dev/uino
A standard device library for Arduino and other -ino's

It's a mess here right now, but work is going on!
The goal with ths project is to create a clean and well-coded library for all kinds of devices attachable to Arduinos.

Currently the source/roadmap file contain the layout for the library.

# Example code
This is a basic example program where a pushbutton and the on-circutboard led (number 13) are used. When the button is pressed the led light up. The button is connected between arduino pin 3 and ground (because then the built-in pullup resistor can be used) and initiated by creating a *Button* object with a *Onboard* pin (onboard the Arduino board) set to use pin number 3. In the loop `button.value()` reads the boolean value if the button is pressed or not.

```cpp
#include <devuino.h>

Button<Onboard> button(Onboard(3), Resistor::PullUp);
Led<Onboard> led(Onboard(13));

void setup()
{
}

void loop()
{
    if (button.value())
    {
        led.off();
    }
    else
    {
        led.on();
    }
}
```


# Devices implemented

✅ == Implemented fully  
🔴 == Not implemented but planned

| Status | Device            | Description                                 |
| :----: | :---------------- | :------------------------------------------ |
| ✅      | **Switch**        | Digital output to switch between on and off |
| ✅      | **Button**        | Digital input between on and off            |
| ✅      | **Potentiometer** | Analog input in bitsize range               |


## Mechanical
---
| Status | Mechanical | Description           |
| :----: | :--------- | :-------------------- |
| 🔴     | **Servo**  | Control generic servo |


## Light
---
| Status | Light        | Description                                 |
| :----: | :----------- | :------------------------------------------ |
| ✅      | **Led**      | Light control on/off and brightness for led |
| ✅      | **LedRgb**   | Same as Led but with 3-pin rgb              |
| ✅      | **LedRgbw**  | Same as Led but with 4-pin rgbw             |
| 🔴     | **Neopixel** | Neopixel/WS2812 1-wire rgb/rgbw led         |


## Sound
---
| Status | Sound             | Description    |
| :----: | :---------------- | :------------- |
| 🔵     | **BuzzerPassive** | Passive buzzer |
| 🔵     | **BuzzerActive**  | Active buzzer  |


## Messuarement
---
| Status | Messuarement | Description             |
| :----: | :----------- | :---------------------- |
| 🔴     | **HCSR04**   | HC-SR04 distance sensor |


## Display
---
| Status | Display     | Description                         |
| :----: | :---------- | :---------------------------------- |
| 🔴     | **Max72xx** | Max 7219/7221 seven-segment display |