# Cyclops Bot

An ESP32-powered robotics project controlled via Bluetooth Low Energy (BLE) using an Xbox Series X/S controller. Cyclops Bot features dynamic multi-servo continuous sweeping controls, an I2C OLED display with custom animated face graphics, and a modular PCB pin architecture.

---

## Overview

Cyclops Bot interfaces an ESP32 microcontroller with an Xbox Series X/S controller over BLE using the XboxSeriesXControllerESP32_asukiaaa library. It translates controller inputs (triggers, bumpers, and buttons) into smooth position updates across 8 independent servo channels while maintaining an expressive OLED display interface.

### Key Features
- **BLE Wireless Control:** Connects natively to Xbox Series X/S controllers without dongles.
- **Smooth Sweep Engine:** Uses non-blocking position updates (SWEEP_SPEED = 1.0) to provide smooth, continuous servo sweeps.
- **Multi-Servo Support:** Drives up to 8 independent servos with preset angle bounds and default stances.
- **Dedicated Custom PCB:** Integrates power regulation, signal breakout headers, and I2C lines directly on a custom carrier board.
- **Expressive OLED Interface:** Displays an animated robot face on an I2C SSD1306 display.
- **Non-blocking Execution:** Employs FreeRTOS task delays (vTaskDelay) to preserve system cycles for background Bluetooth execution and prevent Watchdog Timer (WDT) resets.

---

## Hardware Architecture & Custom PCB

Cyclops Bot utilizes a custom printed circuit board (PCB) designed to consolidate component connections, isolate heavy motor current loads, and eliminate loose jumper wiring.

<img width="832" height="1320" alt="pcbpic" src="https://github.com/user-attachments/assets/9e0f97da-663b-4e6c-9f2e-1ac2a3c901a3" />

### PCB Hardware Specifications
- **Microcontroller Socket:** Dual female header rails designed to fit standard 30-pin ESP32 Dev Module footprint.
- **Servo Header Rail (H1–H8):** 8 sets of 3-pin male headers (GND, VCC, Signal) wired directly to dedicated ESP32 GPIOs.
- **Power Separation Plane:** Isolated high-current 5V bus powering the servo headers separately from the ESP32 logic power rail.
- **Display Terminal:** 4-pin I2C breakout header providing 3.3V/5V, GND, SDA (GPIO 21), and SCL (GPIO 22).
- **Filtering Capacitors:** On-board decoupling capacitors across the servo power rail to absorb transient voltage dips and prevent brownout resets during peak motor draws.

---

## Components Required

### Microcontroller & Display
- **ESP32 Development Board** (e.g., ESP32 Dev Module)
- **Cyclops Bot Custom PCB**
- **0.96" SSD1306 OLED Display** (128x64 pixels, I2C interface)

### Actuators & Power
- **8x Micro Servos** (e.g., SG90, MG90S, or similar 5V servos)
- **External 5V DC Power Supply** (Minimum 3A recommended to handle servo stall currents)
- **Common Ground Line** (Tying external power GND to ESP32 GND via PCB plane)

### Controller
- **Xbox Series X/S Wireless Controller** (Updated with standard BLE firmware, non-controller option available)

---

## Wiring & Pin Mapping

> **Important:** Never power 8 servos directly from the ESP32's 3.3V or 5V pins. Always route the external 5V power supply to the PCB's main power screw terminal or power jack.

### Servo Pin Assignments

| PCB Servo Header | Target Motor | ESP32 GPIO Pin | Motion Limits (Min / Attention / Max) | Control Trigger/Button |
| :--- | :--- | :--- | :--- | :--- |
| **H1** | Motor 1 | **GPIO 13** |  
| **H2** | Motor 2 | **GPIO 12** | 
| **H3** | Motor 3 | **GPIO 27** | 
| **H4** | Motor 4 | **GPIO 14** | 
| **H5** | Motor 5 | **GPIO 26** |
| **H6** | Motor 6 | **GPIO 25** |
| **H7** | Motor 7 | **GPIO 33** | 
| **H8** | Motor 8 | **GPIO 32** |

### OLED Display Pin Assignments (I2C)

| SSD1306 Pin | PCB Header / ESP32 GPIO Pin |
| :--- | :--- |
| **VCC** | 3.3V / 5V Rail |
| **GND** | Common GND Plane |
| **SDA** | **GPIO 21** |
| **SCL** | **GPIO 22** |

---
## Xbox Controller Mappings

| Control Input | Action / Motion |
| :--- | :--- |
| **Left Joystick (Forward)** | Move Forward |
| **Left Joystick (Backwards)** | Move Backwards |
| **Left Joystick (Left / Right)** | Move Sideways |
| **Hold RT (Right Trigger)** | Rotate Front Right |
| **Hold RB (Right Bumper)** | Rotate Back Right |
| **Hold LT (Left Trigger)** | Rotate Front Left |
| **Hold LB (Left Bumper)** | Rotate Back Left |
| **Button A** | Attention Stance |
| **Button X** | Wave Gesture |

## Setup & Installation Instructions

### 1. Software Requirements
Ensure you have the **Arduino IDE** installed along with the ESP32 board package (`esp32` by Espressif Systems).

### 2. Install Required Libraries
Open the **Library Manager** in Arduino IDE (`Tools` -> `Manage Libraries...`) and install the following:

- **ESP32Servo** by Kevin Harrington
- **Adafruit_GFX** by Adafruit
- **Adafruit_SSD1306** by Adafruit
- **XboxSeriesXControllerESP32_asukiaaa** by Asuki Kono

### 3. Board & IDE Settings
Select your board configuration under **Tools**:
- **Board:** ESP32 Dev Module
- **Partition Scheme:** Huge APP (3MB No OTA/1MB SPIFFS) *(Required for BLE stack compilation)*
- **Upload Speed:** 115200

### 4. Upload & Pairing Procedure
1. Connect your ESP32 to your computer via USB and upload the sketch.
2. Open the **Serial Monitor** set to **115200 baud**.
3. Turn on your Xbox controller and hold the **Pairing Button** on top until the Xbox symbol flashes rapidly.
4. Keep the controller within close proximity to the ESP32. The Xbox button light will turn solid once successfully paired.
