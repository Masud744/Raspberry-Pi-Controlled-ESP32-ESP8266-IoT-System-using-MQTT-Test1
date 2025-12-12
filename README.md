# Raspberry Pi Controlled ESP32–ESP8266 IoT System using MQTT

A complete **MQTT-based distributed IoT project** where a **Raspberry Pi** works as the central controller and MQTT broker, an **ESP32** performs ultrasonic distance sensing, and an **ESP8266 (NodeMCU)** controls an LED based on proximity logic.

---

## 📌 Project Overview

This project demonstrates a real-world **publish–subscribe IoT architecture** using the **MQTT protocol**. Instead of direct device-to-device communication, all nodes communicate through a central broker running on a Raspberry Pi.

**Core idea:**
When an object comes within a predefined distance threshold (10 cm), the LED connected to ESP8266 turns **ON** automatically; otherwise, it turns **OFF**.

---

## 🧠 System Architecture

```
ESP32 (Ultrasonic Sensor Node)
        |
        |  MQTT Publish: iot/esp32/distance
        v
Raspberry Pi (MQTT Broker + Controller)
        |
        |  MQTT Publish: iot/esp8266/led
        v
ESP8266 / NodeMCU (LED Actuator Node)
```

---

## 🔩 System Components & Roles

### 🧠 Raspberry Pi (Central Controller)

* Runs Mosquitto MQTT Broker
* Executes Python control logic
* Subscribes to sensor data
* Publishes actuator commands
* Acts as the decision-making unit of the system

### 📡 ESP32 (Sensor Node)

* Interfaces with ultrasonic sensor
* Measures distance in centimeters
* Publishes distance data to MQTT broker
* Works as an independent sensing node

### 💡 ESP8266 / NodeMCU (Actuator Node)

* Subscribes to control commands
* Controls LED based on MQTT messages
* Executes actions without knowing sensor logic

---

## 📂 Repository Structure

```
RaspberryPi-ESP32-ESP8266-MQTT-IoT/
│
├── raspberry-pi/
│   └── distance_controller.py
│
├── esp32/
│   └── ESP32_Final_t.ino
│
├── esp8266/
│   └── nodeMCU_Final_t.ino
│
├── README.md
└── LICENSE
```

---

## 🔁 MQTT Topics Used

| Topic                | Publisher    | Subscriber   | Description               |
| -------------------- | ------------ | ------------ | ------------------------- |
| `iot/esp32/distance` | ESP32        | Raspberry Pi | Publishes distance in cm  |
| `iot/esp8266/led`    | Raspberry Pi | ESP8266      | Sends LED ON/OFF commands |

---

## ⚙️ Hardware Requirements

* Raspberry Pi (3 / 4)
* ESP32 Development Board
* ESP8266 / NodeMCU
* Ultrasonic Sensor (HC-SR04 or equivalent)
* LED + Resistor
* Jumper Wires
* Power Supply

---

## 🛠 Software & Tools

* Raspberry Pi OS
* Mosquitto MQTT Broker
* Python 3
* Paho MQTT (Python library)
* Arduino IDE

---

## 🚀 Working Principle

1. ESP32 measures distance using ultrasonic sensor
2. Distance value is published to MQTT broker
3. Raspberry Pi receives sensor data
4. Control logic compares distance with threshold
5. Raspberry Pi publishes LED command (ON/OFF)
6. ESP8266 receives command and controls LED

---

## 🎥 Demonstration

Demo videos showing real-time system operation are available in the `media/` directory.

---

## 🎯 Applications

* Smart proximity-based lighting
* IoT learning and academic projects
* Distributed sensor–actuator systems
* Smart security and automation

---

## 🔮 Future Enhancements

* Multiple ESP32 sensor nodes
* Database logging (MySQL / Google Sheets)
* Web dashboard for monitoring
* AI/ML-based adaptive thresholding
* Mobile app integration

---

## 📜 License

This project is licensed under the **MIT License**.

---

## 👨‍💻 Author

**Shahriar Alom Masud**
B.Sc. in IoT & Robotics Engineering University of Frontier Technology, Bangladesh
Passionate about IoT, Robotics, AI and ML
Email: [shahriar0002@std.uftb.ac.bd](mailto:shahriar0002@std.uftb.ac.bd)
LinkedIn: https://www.linkedin.com/in/shahriar-alom-masud
