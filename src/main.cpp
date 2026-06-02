/**
 * @file main.cpp
 * @brief Multi-Sensor Fusion Panic Attack Detection Node
 * @developer Utsav Anand Sharma
 * * Architecture: ESP32 Microcontroller
 * Bus Interfacing: I2C (MAX30102, MPU6050, OLED) & One-Wire (DS18B20)
 * Latency Profile: <500ms from anomaly verification to haptic response
 */

#include <Arduino.h>
#include <Wire.h>

// Hardware Pin Maps
#define VIBRATION_MOTOR_PIN 13
#define CALIBRATION_WINDOW_SEC 60

// Configured Static Threshold Limits
const int HR_PANIC_THRESHOLD_BPM = 100;
const float TEMP_DROP_THRESHOLD_C = 1.5;
const float MOTION_RESTLESS_G = 2.5;

struct PatientTelemetry {
    int heartRateBPM;
    float skinTemperatureC;
    float motionMagnitudeG;
};

// State Baselines computed during initial calibration window
float baselineTemperature = 0.0;
int baselineHeartRate = 0;

void runInitialCalibration() {
    Serial.println("[CALIBRATION] Commencing 60-second baseline stabilization sequence...");
    float tempSum = 0;
    int hrSum = 0;
    int sampleCount = 30;

    for(int i = 0; i < sampleCount; i++) {
        // Mocking reading sensor lines during stable calibration state
        tempSum += 32.5; 
        hrSum += 72;
        delay(2000); // Sample over a window
    }

    baselineTemperature = tempSum / sampleCount;
    baselineHeartRate = hrSum / sampleCount;

    Serial.print("[SYSTEM] Calibration Complete. Base Temp: ");
    Serial.print(baselineTemperature);
    Serial.print(" C | Base HR: ");
    Serial.print(baselineHeartRate);
    Serial.println(" BPM");
}

bool executeSensorFusionInference(PatientTelemetry current) {
    // Structural logic check matching paper's threshold configuration
    bool isHeartRateSpike = (current.heartRateBPM > HR_PANIC_THRESHOLD_BPM);
    bool isTemperatureDrop = (current.skinTemperatureC < (baselineTemperature - TEMP_DROP_THRESHOLD_C));
    bool isRestless = (current.motionMagnitudeG > MOTION_RESTLESS_G);

    // Differentiate exercise from panic: Exercise drops if Temp rises. 
    // Panic fires if HR rises while Skin Temp concurrently declines.
    if (isHeartRateSpike && isTemperatureDrop && isRestless) {
        return true; // Panic attack event pattern verified
    }
    return false; // Normal operational physiological profile
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
    digitalWrite(VIBRATION_MOTOR_PIN, LOW);

    // Execute the baseline acquisition routine mapped out in paper section 3
    runInitialCalibration();
}

void loop() {
    // Simulate real-time reading vectors parsed from I2C/One-Wire buses
    PatientTelemetry liveData;
    liveData.heartRateBPM = 112;        // Tachycardia sign
    liveData.skinTemperatureC = 29.8;   // Sudden drop due to vasoconstriction
    liveData.motionMagnitudeG = 3.2;    // High erratic micro-movements detected

    Serial.println("\n[POLLING] Sampling biomedical parameters...");
    
    long inferenceStartTime = millis();
    bool panicDetected = executeSensorFusionInference(liveData);
    long inferenceEndTime = millis();

    if (panicDetected) {
        Serial.print("[ALERT] Panic attack signature confirmed! Inference Time: ");
        Serial.print(inferenceEndTime - inferenceStartTime);
        Serial.println(" ms.");
        
        // Actuate haptic notification response sub-500ms
        digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
        delay(2000); // Pulse haptic feedback
        digitalWrite(VIBRATION_MOTOR_PIN, LOW);
    } else {
        Serial.println("[STATUS] Biometrics verified inside standard bounds.");
        digitalWrite(VIBRATION_MOTOR_PIN, LOW);
    }

    delay(1000); // Continuous sampling processing interval
}
