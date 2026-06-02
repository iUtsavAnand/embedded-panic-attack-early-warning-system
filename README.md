# Embedded Early Warning System for Panic Attacks (ANS Response Patterns)

An ESP32-powered wearable hardware platform that utilizes sensor fusion to monitor physiological markers of the Autonomic Nervous System (ANS), enabling the real-time detection and mitigation of panic attacks.

## 📁 Repository Overview
* **/src**: Contains the core hardware initialization scripts, multi-parameter threshold state-machines, and sensor read loops.
* **/hardware**: Includes hardware block diagrams, pin-out configurations, and component datasheets.
* **/docs**: Houses the formal IEEE conference format seminar report and research references.

## 🧠 Sensor Fusion Logic Flow
Unlike single-parameter systems prone to false negatives or positives, this framework cross-examines Heart Rate, Skin Temperature, and Motion Activity to classify user states deterministically:

                      +---------------------------------------+
                      | Sample Live Sensor Matrix (100Hz Loop)|
                      +---------------------------------------+
                                          |
                                          v
                      +---------------------------------------+
                      | Parse Data: MAX30102, MPU6050, DS18B20|
                      +---------------------------------------+
                                          |
                                          v
                        /-----------------------------------\
                       /  Is HR > Threshold AND Skin Temp    \
                      <   Decreasing AND Motion = Restless?   >
                       \                                     /
                        \-----------------------------------/
                                   /                 \
                            YES   /                   \   NO
                                 /                     \
                                v                       v
              +-----------------------------------+   +-----------------------+
              | Trigger Immediate Haptic Response |   | Maintain Normal State |
              |  (Vibration Motor Active <500ms)  |   | System Polling Loop   |
              +-----------------------------------+   +-----------------------+

## 📄 Research & Publications
The structural engineering architecture, experimental data, and cost benchmarks are fully documented in our academic seminar paper.

* **Read the Full Paper:** [Panic_Attack_Detection_System_IEEE.pdf](./docs/Microprocessors_and_Microcontrollers_Submission.pdf)

**Developed by:** Utsav Anand Sharma, Nikunj Goydani, Harsh Batra, & Prasoon Mishra  
**Affiliation:** School of Electronics Engineering, Vellore Institute of Technology
