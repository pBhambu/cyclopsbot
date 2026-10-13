#  Wiring Guide

This document outlines the power distribution, pin mapping, and step-by-step wiring instructions.
---

## Power Structure

To prevent ESP32 brownouts and screen resets caused by high current spikes from the 8 micro servos, this build uses a **split-rail power design**:
* **High-Current Rail:** Servos draw power directly from a regulated DC-DC buck converter.
* **Logic Rail:** The ESP32 and OLED display share power safely alongside the control signals, ensuring a common ground across all components.

### Pin Mapping Reference

| Component / Function | ESP32 GPIO Pin | Description |
| :--- | :--- | :--- |
| **Servo R1** | GPIO 13 | Front Right Hip |
| **Servo R2** | GPIO 12 | Back Right Hip |
| **Servo L1** | GPIO 27 | Front Left Hip |
| **Servo L2** | GPIO 14 | Back Left Hip |
| **Servo R3** | GPIO 26 | Front Right Lift |
| **Servo R4** | GPIO 25 | Back Right Lift |
| **Servo L3** | GPIO 33 | Front Left Lift |
| **Servo L4** | GPIO 32 | Back Left Lift |
| **OLED SDA** | GPIO 21 | I2C Data Line |
| **OLED SCL** | GPIO 22 | I2C Clock Line |

---

## Step-by-Step Wiring Instructions

> **SAFETY WARNING:** Double-check all polarity before plugging in your battery.

### 1. Set up the Main Power Distribution
1. Configure your high-current DC-DC Buck Converter (e.g., LM2596) to output exactly **5.0V** using a multimeter before connecting any electronics.
2. If needed, connect an XT30 pigtail to your LiPo Battery
3. Connect the **Negative (-)** wire from your LiPo battery to the **IN-** terminal of the buck converter.
4. Connect the **Positive (+)** wire from your LiPo battery to the **IN+** terminal of the buck converter.
5. The **OUT+** terminal ($5\text{V}$) of the converter forms your main **Servo Power Rail**.
6. The **OUT-** terminal forms your **System Ground Rail**.

### 2. Connect the Servos
1. 

### 3. Power the ESP32 & OLED Display


### 4. Final Verification
* Ensure every component's Ground pin ties back to the same shared ground rail. A **Common Ground** is mandatory for proper PWM signal transmission and I2C communication.
