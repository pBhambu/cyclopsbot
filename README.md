# cyclopsbot
ESP32-powered robot controlled via Xbox Controller with OLED screen and 8 servos.

---

## Overview

Cyclops Bot interfaces an ESP32 microcontroller with an Xbox Series X/S controller over BLE using the XboxSeriesXControllerESP32_asukiaaa library. It translates controller inputs (triggers, bumpers, and buttons) into smooth position updates across 8 independent servo channels while maintaining an expressive OLED display interface.

### Key Features
- **BLE Wireless Control:** Connects natively to Xbox Series X/S controllers without dongles.
- **Smooth Sweep Engine:** Uses non-blocking position updates (SWEEP_SPEED = 1.0) to provide smooth, continuous servo sweeps.
- **Multi-Servo Support:** Drives up to 8 independent servos with preset angle bounds and default stances.
- **Expressive OLED Interface:** Displays an animated robot face on an I2C SSD1306 display.
- **Non-blocking Execution:** Employs FreeRTOS task delays (vTaskDelay) to preserve system cycles for background Bluetooth execution and prevent Watchdog Timer (WDT) resets.

---

## Components Required

### Microcontroller & Display
- **ESP32 Development Board** (e.g., ESP32 Dev Module)
- **0.96" SSD1306 OLED Display** (128x64 pixels, I2C interface)

### Actuators & Power
- **8x Micro Servos** (e.g., SG90, MG90S, or similar 5V servos)
- **External 5V DC Power Supply** (Minimum 3A recommended to handle servo stall currents)
- **Common Ground Line** (Tying external power GND to ESP32 GND)

### Controller
- **Xbox Series X/S Wireless Controller** (Updated with standard BLE firmware)

---

## Wiring & Pin Mapping

> **Important:** Never power 8 servos directly from the ESP32's 3.3V or 5V pins. Always use an external 5V power supply to power the servo VCC/GND lines and share a common ground with the ESP32.

### Servo Pin Assignments

| Servo Header | Target Motor | ESP32 GPIO Pin | Motion Limits (Min / Attention / Max) | Control Trigger/Button |
| :--- | :--- | :--- | :--- | :--- |
| **H1** | Motor 1 | **GPIO 13** | 90.0° / 135.0° / 180.0° | Hold **RT** (Right Trigger) |
| **H2** | Motor 2 | **GPIO 12** | 0.0° / 45.0° / 90.0° | Hold **RB** (Right Bumper) |
| **H3** | Motor 3 | **GPIO 27** | 0.0° / 45.0° / 90.0° | Hold **LT** (Left Trigger) |
| **H4** | Motor 4 | **GPIO 14** | 90.0° / 135.0° / 180.0° | Hold **LB** (Left Bumper) |
| **H5** | Motor 5 | **GPIO 26** | 0.0° / 90.0° / 180.0° | Expansion Channel |
| **H6** | Motor 6 | **GPIO 25** | 0.0° / 90.0° / 180.0° | Expansion Channel |
| **H7** | Motor 7 | **GPIO 33** | 0.0° / 90.0° / 180.0° | Expansion Channel |
| **H8** | Motor 8 | **GPIO 32** | 0.0° / 90.0° / 180.0° | Expansion Channel |

### OLED Display Wiring (I2C)

| SSD1306 Pin | ESP32 GPIO Pin |
| :--- | :--- |
| **VCC** | 3.3V / 5V |
| **GND** | GND |
| **SDA** | **GPIO 21** |
| **SCL** | **GPIO 22** |

---

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
