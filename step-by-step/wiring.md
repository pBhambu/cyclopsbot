#  Wiring Guide

This document outlines the power distribution, pin mapping, and step-by-step wiring instructions.
---

## Power Structure

To prevent ESP32 brownouts and screen resets caused by high current spikes from the 8 micro servos, this build uses a **split-rail power design**:
* **High-Current Rail:** Servos draw power directly from a regulated DC-DC buck converter.
* **Logic Rail:** The ESP32 and OLED display share power safely alongside the control signals, ensuring a common ground across all components.

### Servo Pin Mapping Reference

| Component / Function | PCB Pin | Description |
| :--- | :--- | :--- |
| **Servo R1** | H1 | Front Right Hip |
| **Servo R2** | H2 | Back Right Hip |
| **Servo L1** | H3 | Front Left Hip |
| **Servo L2** | H4 | Back Left Hip |
| **Servo R3** | H5 | Front Right Lift |
| **Servo R4** | H6 | Back Right Lift |
| **Servo L3** | H7 | Front Left Lift |
| **Servo L4** | H8 | Back Left Lift |

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
