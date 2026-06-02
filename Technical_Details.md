# Technical Breakdown: ANS Panic Attack Detection System

### Project Vision
[cite_start]Panic attacks manifest rapidly through acute physical symptoms like tachycardia, intense diaphoresis, and sudden restlessness[cite: 20, 30]. [cite_start]Traditional consumer wearables monitor basic daily activity levels and lack the multi-modal sensor arrays needed to track acute psychological distress windows in real-time[cite: 31, 32]. [cite_start]This project builds a low-latency edge node capable of continuous data logging and instantaneous haptic feedback to help users mitigate attacks early[cite: 25, 32, 33].

---

### System Architecture & Hardware Interfacing
[cite_start]The hardware topography is separated into three decoupled operational layers[cite: 45]:


1. **Input Sensing Matrix:**
   * [cite_start]**MAX30102:** High-sensitivity pulse oximeter and heart-rate sensor communicating over the I2C protocol[cite: 46, 71].
   * [cite_start]**MPU6050:** 6-axis Inertial Measurement Unit (IMU) used to track sudden, jerky micro-movements associated with somatic restlessness[cite: 47, 80].
   * [cite_start]**DS18B20:** Digital thermometer operating over a One-Wire bus to log subtle changes in peripheral skin temperature[cite: 47, 71].
2. [cite_start]**Processing Core:** An ESP32 microcontroller executing calibration matrices, managing software queues, and firing interrupts[cite: 49, 72].
3. [cite_start]**Output Actuation Layer:** A 0.96" I2C OLED interface paired with a low-voltage DC vibration motor to provide immediate physical counter-feedback (<500ms response time)[cite: 50, 71, 79].

---

### The Sensor Fusion Differentiation Matrix
[cite_start]Single-sensor devices frequently misinterpret physical exercise as a panic event because both cause elevated heart rates[cite: 38, 39, 77]. [cite_start]This system utilizes multi-parameter cross-examination to eliminate false positives[cite: 26, 68]:

| Dynamic User State | Heart Rate (MAX30102) | Skin Temperature (DS18B20) | Motion Profiling (MPU6050) | System Action |
| :--- | :--- | :--- | :--- | :--- |
| **Physical Exercise** | Elevated 📈 | [cite_start]Elevated 📈 [cite: 77] | [cite_start]High / Rhythmic [cite: 77] | [cite_start]**No Alarm** (Normal Calibration) [cite: 77] |
| **Panic Attack Window**| [cite_start]Elevated 📈 [cite: 30, 78] | [cite_start]Decreased 📉 [cite: 78] | [cite_start]High / Erratic (Restless) [cite: 67, 80] | [cite_start]**Trigger Alert** (<500ms Haptics) [cite: 67, 78, 79] |

---

### Cost Analysis Realization
[cite_start]Designed explicitly for large-scale, low-cost accessibility, the hardware configuration is highly optimized[cite: 87]:

| Core Component | Quantity | Unit Cost (INR) | Primary Sub-System Role |
| :--- | :--- | :--- | :--- |
| **ESP32 MCU** | 1 | 500 | [cite_start]Core Clock, Inter-IC Bus Master, Algorithm Execution [cite: 49, 71, 89] |
| **MAX30102** | 1 | 300 | [cite_start]Photoplethysmography (PPG) Heart Rate Sampling [cite: 46, 89] |
| **MPU6050** | 1 | 200 | [cite_start]Tri-Axial Accelerometer Movement Detection [cite: 47, 89] |
| **DS18B20** | 1 | 120 | [cite_start]One-Wire Peripheral Temperature Tracking [cite: 47, 71, 89] |
| **OLED Display**| 1 | 200 | [cite_start]Live Local Telemetry Visualization [cite: 50, 89] |
| **Vibration Motor**| 1| 150 | [cite_start]Sub-500ms Latency Emergency Haptic Alert [cite: 50, 79, 89] |
| **Total System Cost**| | **1470 INR** | [cite_start]Fully Deployable Open-Source Prototype [cite: 87, 89] |

---

### Technical Specifications
* [cite_start]**Languages & Environments:** Embedded C/C++, Arduino IDE [cite: 70]
* [cite_start]**Communication Standards:** I2C Protocol, Dallas One-Wire Bus Protocol [cite: 71]
* [cite_start]**Core Design Techniques:** Multi-Sensor Data Fusion, Real-time Baseline Calibration, Low-Latency Actuation, Haptic Feedback Design [cite: 26, 72, 118]
