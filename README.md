# Smart Safe Project - ATmega328P / Arduino Nano

This repository contains an embedded systems project developed for an Arduino Nano / ATmega328P board.
The project implements a smart safe system using potentiometers as a combination lock, IR detection for door/object sensing, vibration detection for tamper alarm, EEPROM memory for saving the last valid combination, LEDs for visual feedback, and a passive buzzer for sound alerts.


## Features

- **No Arduino Libraries**: Direct register manipulation for maximum control and efficiency.
- **Potentiometer-based safe code**: Three potentiometers are used as the combination input.
- **Red / Green status LEDs**: 
        Red LED ON: potentiometers are not aligned correctly. Green LED ON: all potentiometers are in the correct position.
- **IR obstacle sensor**: Used to detect whether the safe door/object is in position. Helps trigger the alarm when the safe is not in a correct state.
- **Vibration sensor**: KY-002 vibration sensor connected to an external interrupt pin. Used for tamper detection. If vibration is detected, the buzzer alarm is triggered.
- **Passive buzzer alarm**: Generates sound using manual HIGH/LOW switching. Used for wrong state warning and vibration alarm.
- **EEPROM memory**: Stores the last saved potentiometer combination. The safe remembers the last valid values.

## Hardware Components

- Arduino Nano / ATmega328P
- 3x Potentiometers
- 3x LEDs for potentiometer status
- 1x Red LED
- 1x Green LED
- 1x Passive buzzer
- 1x IR obstacle avoidance sensor
- 1x KY-002 vibration sensor


## Future Improvements
- Add a reset button for EEPROM values.
- Add LCD1602 display for messages.
- Add wrong attempt counter.
- Add lockout mode after multiple failed attempts.
- Add separate source files for buzzer, sensors, and safe logic.
- Add USART debugging output for reading live potentiometer values.

