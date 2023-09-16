# Smart Car Parking STM32

A Smart Car Parking system implemented on an STM32 microcontroller. This system allows admin users to manage allowed IDs for entrance, monitors available parking slots, and controls access using RFID cards, a servo motor, and a PIR sensor.

## Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Key Features](#key-features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)


## Hardware Requirements

- STM32 microcontroller 
- Keypad
- LCDs display
- RFID readers
- Servo motors
- PIR sensor
- RFID cards

## Software Requirements

- STM32CubeIDE or STM32CubeMX for firmware development
- MCAL and HAL Drivers for STM32
- Proteus


## Key Features

1. **Admin Control:**
   - Administrators can manage allowed entrance IDs using a keypad and LCD display.
   - Admins have the option to add new IDs, delete individual IDs, or delete all IDs from the system.

2. **User-Friendly Interface:**
   - The LCD display provides real-time information, including the number of available parking slots and the name of the parking facility.
   
3. **RFID Access Control:**
   - Users can enter the parking facility by presenting their RFID cards.
   - The system compares the presented RFID card with the allowed IDs.
   - If a match is found, a confirmation message is displayed, and the servo motor opens the entrance gate.

4. **Occupancy Monitoring:**
   - The system employs a PIR sensor to detect the presence of a user's car inside the parking area.
   - The servo motor remains open as long as the PIR sensor detects the car, ensuring safe entry.
   - The servo motor closes the gate when the PIR sensor no longer detects the car, facilitating exit.

5. **Automatic Slot Management:**
   - The system automatically updates the number of available parking slots based on entries and exits.
   - Slots are decremented when someone enters and incremented when someone exits.



## Project Structure

- **Documentation:** Project documentation and schematics.
- **Source Code:** Main application code.
- **HAL Layer:** (KeyPad, Lcd, Servo Motor, LEDs, PIRs).
- **MCAL Layer:** (GPIO, RCC, USART, TIMER, Device header file).
- **Simulation File:** (Proteus)
- **README.md:** This file.


## Getting Started

1. Clone this repository to your local development environment.
2. Set up the development environment using STM32CubeIDE or STM32CubeMX.
3. Configure the necessary peripherals, pins, and interrupts based on your hardware setup.
4. Integrate required libraries for components like the LCD, RFID reader, and servo motor.
