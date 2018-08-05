# /dev/uino
A standard device library for Arduino and other -ino's

It's a mess here right now, but work is going on!
The goal with ths project is to create a clean and well-coded library for all kinds of devices attachable to Arduinos.

Currently the source/roadmap file contain the layout for the library.

Basic devices




| **Ö**                | test                                        |

# Devices implemented

🔵 == Implemented fully  
🔴 == Not implemented but planned

| Status | Device            | Description                                 |
| :----: | :---              | :---                                        |
| 🔵     | **Switch**        | Digital output to switch between on and off |
| 🔵     | **Button**        | Digital input between on and off            |
| 🔵     | **Potentiometer** | Analog input in bitsize range               |

| Mechanical   |                       |
| ------------ | --------------------- |
| 🔴 **Servo** | Control generic servo |

| Light           |                                             |
| --------------- | ------------------------------------------- |
| 🔵 **Led**      | Light control on/off and brightness for led |
| 🔵 **LedRgb**   | Same as Led but with 3-pin rgb              |
| 🔵 **LedRgbw**  | Same as Led but with 4-pin rgbw             |
| 🔴 **Neopixel** | Neopixel/WS2812 1-wire rgb/rgbw led         |

| Sound                |                |
| -------------------- | -------------- |
| 🔵 **BuzzerPassive** | Passive buzzer |
| 🔵 **BuzzerActive**  | Active buzzer  |

| Distance      |                         |
| ------------- | ----------------------- |
| 🔴 **HCSR04** | HC-SR04 distance sensor |

| Display        |                                     |
| -------------- | ----------------------------------- |
| 🔴 **Max72xx** | Max 7219/7221 seven-segment display |
