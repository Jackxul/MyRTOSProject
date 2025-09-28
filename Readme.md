# Smart Temperature-Humidity Control System  
*A FreeRTOS-based IoT project using ESP8266 and Raspberry Pi*  

---

## 📖 Project Overview
This project implements a **real-time temperature and humidity monitoring system** with **automatic control** using **ESP8266 + FreeRTOS**.  

- **ESP8266** handles:
  - Sensor data acquisition (DHT22 / DS18B20)
  - Motor and LED control
  - WiFi data transmission to Raspberry Pi  
- **Raspberry Pi** is responsible for:
  - Receiving data from ESP8266
  - Displaying the latest temperature/humidity and alerts on an **I2C LCD**  

The project emphasizes **RTOS concepts** including **multi-tasking, Mutex, Semaphore, and interrupt handling**.  

---

## 🎯 Key Features
- **Sensor Monitoring**: Periodic reading of DHT22 / DS18B20 values.  
- **Interrupt Trigger**: Abnormal values trigger an interrupt that signals control actions.  
- **Automatic Control**: Motor and LED are activated when thresholds are exceeded.  
- **Task Synchronization**:  
  - **Binary Semaphore**: Used for interrupt-to-task signaling.  
  - **Mutex**: Protects shared resources (LED, motor state, WiFi buffer).  
- **WiFi Communication**: ESP8266 uploads data to Raspberry Pi.  
- **LCD Output**: Raspberry Pi displays real-time readings and alerts on I2C LCD.  

---

## 🛠️ Hardware Requirements
- **2 × ESP8266 WiFi modules**  
- **2 × Raspberry Pi** (any model with I2C support)  
- **Sensors**:  
  - DHT22 (Temperature + Humidity)  
  - DS18B20 (Temperature)  
- **Actuators**:  
  - DC Motor (simulating fan)  
  - LED indicators  
- **I2C LCD display**  
- Miscellaneous: jumper wires, breadboards, resistors, power supply  

---

## 💻 Software Requirements
- **ESP8266 RTOS SDK** (FreeRTOS support included)  
- **FreeRTOS v10+** (already ported in ESP8266 SDK)  
- **Raspberry Pi**:
  - Python or C for UART/WiFi communication  
  - I2C library for LCD (e.g., `smbus2` in Python)  

---

## 📡 System Architecture

+----------------------+ WiFi +----------------------+
| ESP8266 #1 | <-------------> | Raspberry Pi #1 |
|----------------------| |----------------------|
| Sensor Task | | I2C LCD Display |
| - DHT22 / DS18B20 | | - Show Temp/Humidity |
| - Periodic / IRQ | | - Show Alerts |
| | | |
| Control Task | +----------------------+
| - Motor / LED ctrl |
| - Wait for Semaphore |
| - Mutex for resource |
| |
| WiFi Upload Task |
| - Send data to Pi |
| - Mutex for buffer |
+----------------------+


---

## 🔄 Task Design (ESP8266)

| Task | Description | RTOS Mechanism |
|------|-------------|----------------|
| **Sensor Task** | Periodically reads DHT22/DS18B20 values. | Timer, Interrupt |
| **Control Task** | Controls motor/LED when abnormal data detected. | Binary Semaphore, Mutex |
| **WiFi Upload Task** | Sends sensor data to Raspberry Pi. | Queue, Mutex |
| **Optional Timer Task** | Periodic status update. | FreeRTOS Software Timer |

---

## ⚡ Workflow

1. **Initialization**  
   - FreeRTOS tasks, Mutex, and Semaphores are created.  
   - Sensors and peripherals initialized.  

2. **Sensor Monitoring**  
   - Sensor Task reads DHT22/DS18B20 periodically.  
   - If abnormal value detected → GPIO interrupt triggers Binary Semaphore.  

3. **Control Execution**  
   - Control Task receives Semaphore.  
   - Activates motor and LED warning.  

4. **Data Transmission**  
   - WiFi Upload Task packages and sends readings to Raspberry Pi.  
   - Mutex ensures safe buffer access.  

5. **LCD Display**  
   - Raspberry Pi receives sensor data.  
   - Updates I2C LCD with real-time values and alert status.  

6. **Loop Continuation**  
   - FreeRTOS scheduler ensures fair task execution and synchronization.  

---

## 🔧 RTOS Concepts Applied
- **Interrupt Handling**: Sensor abnormal event → ISR → Binary Semaphore.  
- **Binary Semaphore**: Synchronization between ISR and Control Task.  
- **Mutex**: Protects access to shared hardware resources and data buffers.  
- **Queues**: Used for safe communication between Sensor Task and WiFi Task.  
- **Multi-tasking**: Sensor reading, motor control, WiFi communication, and display run concurrently.  

---

## 👥 Team Collaboration (Two Developers)
| Developer A | Developer B |
|-------------|-------------|
| Sensor driver & interrupt logic | Control Task (motor + LED) |
| WiFi upload task | Raspberry Pi LCD display logic |
| FreeRTOS Mutex/Semaphore setup | FreeRTOS Task scheduling integration |

---

## 🚀 Future Extensions
- Add MQTT broker for cloud monitoring.  
- Implement web dashboard on Raspberry Pi.  
- Expand to multiple sensor nodes (ESP8266 cluster).  

---


