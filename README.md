# 🐾 Automatic Pet Feeder System

## 📌 Overview

The **Automatic Pet Feeder System** is an Arduino-based project designed to automate pet feeding using real-time monitoring and sensor-based decision making. It ensures pets are fed on time even when the owner is unavailable.

---

## 🚀 Features

* ⏰ **Scheduled Feeding** using RTC (DS3231)
* 🐶 **Pet Detection** using IR Sensor
* 🍽️ **Food Level Monitoring** using Ultrasonic Sensor
* 🌙 **Automatic Lighting** using LDR
* 🔄 **Servo-controlled Feeding Mechanism**
* 📟 **LCD Display** for real-time status

---

## 🧠 Working Principle

1. The RTC module keeps track of real time.
2. At the scheduled feeding time:

   * If the pet is present → food is dispensed immediately.
   * If not → system waits for 10 seconds.
   * If still no detection → feeding happens anyway.
3. Ultrasonic sensor continuously monitors food level.
4. LDR controls LED lighting based on ambient light.
5. LCD displays:

   * Current time
   * Food level (%)
   * Pet presence

---

## 🧰 Components Used

* Arduino UNO
* IR Sensor (Pet Detection)
* Ultrasonic Sensor (HC-SR04)
* RTC Module (DS3231)
* Servo Motor (SG90)
* LCD Display (16x2 I2C)
* LDR Module
* LED + Resistor
* Power Bank / External 5V Supply
* Breadboard & Jumper Wires

---

## 🔌 Circuit Connections

| Component       | Arduino Pin |
| --------------- | ----------- |
| IR Sensor       | D2          |
| Ultrasonic TRIG | D3          |
| Ultrasonic ECHO | D4          |
| LDR Module      | D7          |
| LED             | D8          |
| Servo Motor     | D9          |
| LCD (SDA)       | A4          |
| LCD (SCL)       | A5          |
| RTC (SDA)       | A4          |
| RTC (SCL)       | A5          |

⚠️ **Note:** Servo motor should be powered using an external 5V source (power bank). Ensure common ground.

---

## 🖥️ Output Display

* `T: HH:MM` → Current Time
* `F: XX%` → Food Level
* `P:Y / P:N` → Pet Presence

---

## 📂 Project Structure

```
📁 Automatic-Pet-Feeder
 ┣ 📜 main.ino
 ┣ 📜 README.md
 ┗ 📷 circuit_diagram.png
```

---

## ▶️ How to Run

1. Connect all components as per circuit diagram.
2. Upload the code to Arduino using Arduino IDE.
3. Set feeding time in code:

   ```cpp
   int feedHour = XX;
   int feedMinute = XX;
   ```
4. Power the system.
5. Observe automatic feeding behavior.

---

## 🔧 Future Improvements

* Mobile App Integration (IoT)
* Multiple Feeding Schedules
* Weight-based food measurement
* Camera-based pet recognition

---

## 🧠 Learning Outcomes

* Embedded systems integration
* Sensor interfacing
* Real-time processing
* Automation logic design

---

## 🎯 Conclusion

This project demonstrates an efficient and reliable solution for automated pet feeding using multiple sensors and real-time decision-making.

---

## 👨‍💻 Author

Harish
(AIML Engineering Student)

---

## ⭐ If you like this project

Give it a ⭐ on GitHub!
