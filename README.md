## Team Members
**SHIVA SHARAN REDDY** | 2451-23-749-007 |




# IoT Gas Leakage Monitoring & Alert System

A smart, internet-connected Gas Leakage Monitoring and Alert System built using the **ESP32** microcontroller and **Thinger.io** IoT cloud platform. The system continuously polls an **MQ-2 gas sensor**, computes a stable running average to reduce sensor noise, controls local status indicator LEDs, and publishes real-time telemetry to a cloud dashboard.

---

## 🚀 Features

- **Real-Time Gas Detection**: Continuous monitoring of ambient air using the MQ-2 sensor.
- **Noise Reduction & Signal Averaging**: Automatically averages 10 readings per cycle to eliminate ADC noise and false alarms.
- **Dual LED Alert System**:
  - 🟢 **Green LED (GPIO 26)**: Indicates normal/safe conditions.
  - 🔴 **Red LED (GPIO 25)**: Illuminates immediately when gas concentration exceeds the threshold.
- **Cloud Dashboard Integration**: Seamlessly updates Thinger.io with raw ADC values, mapped gas percentages, and status alerts.
- **Over-the-Air Status Updates**: Easily monitor the system status remotely on any device via a browser or mobile app.

---

## 🛠️ Hardware Requirements

| Component | Pin / Connection | Description |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | MCU | Dual-core processing unit with built-in Wi-Fi |
| **MQ-2 Gas Sensor** | `GPIO 34` (Analog input) | Sensor for LPG, Propane, Hydrogen, and Smoke |
| **Red LED** | `GPIO 25` | Warning/Alert indicator (with $220\Omega$ resistor) |
| **Green LED** | `GPIO 26` | Normal/Safe indicator (with $220\Omega$ resistor) |
| **Breadboard & Jumpers** | — | For prototyping and connections |

---

## 📊 Schematic / Connection Guide

1. **MQ-2 Gas Sensor**:
   - `VCC` ➡️ ESP32 `VIN` (5V) or `3.3V` (depending on the sensor module version)
   - `GND` ➡️ ESP32 `GND`
   - `AO` (Analog Output) ➡️ ESP32 `GPIO 34`
2. **Red LED**:
   - Anode (Long leg) ➡️ ESP32 `GPIO 25` (via $220\Omega$ resistor)
   - Cathode (Short leg) ➡️ ESP32 `GND`
3. **Green LED**:
   - Anode (Long leg) ➡️ ESP32 `GPIO 26` (via $220\Omega$ resistor)
   - Cathode (Short leg) ➡️ ESP32 `GND`

---

## ⚙️ Software Setup & Installation

### 1. Arduino IDE Setup
1. Open the Arduino IDE.
2. Go to **File > Preferences** and add the ESP32 board URL under **Additional Boards Manager URLs**:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools > Board > Boards Manager**, search for `esp32`, and install the **esp32** core.
4. Go to **Sketch > Include Library > Manage Libraries**, search for `thinger.io`, and install the **Thinger.io** library.

### 2. Configure Credentials
> [!WARNING]
> Before compiling and flashing the sketch, open [sketch_jun23a.ino](sketch_jun23a/sketch_jun23a.ino) and update the credentials placeholder values with your Wi-Fi credentials and Thinger.io device authorization details:

```cpp
// Thinger.io Credentials
#define USERNAME     "YOUR_THINGER_USERNAME"
#define DEVICE_ID    "YOUR_DEVICE_ID"
#define DEVICE_CRED  "YOUR_DEVICE_CREDENTIALS"

// WiFi Credentials
#define SSID         "YOUR_WIFI_SSID"
#define SSID_PASSWORD "YOUR_WIFI_PASSWORD"
```

### 3. Flash the ESP32
1. Connect your ESP32 to your PC/Mac using a micro-USB cable.
2. Select your correct board (e.g., `DOIT ESP32 DEVKIT V1`) and your COM Port under **Tools > Board / Port**.
3. Click the **Upload** button.

---

## ☁️ Thinger.io Cloud Configuration

1. Create a free account at [Thinger.io](https://thinger.io/).
2. Under **Devices**, click **Add Device** and configure:
   - **Device ID**: Same as `DEVICE_ID` in your code (e.g. `GAS_Detection`).
   - **Device Description**: `Smart Gas Monitoring System`.
   - **Device Credentials**: Same as `DEVICE_CRED` in your code.
3. Once the ESP32 connects to Wi-Fi, the device status on the console dashboard will show as **Connected**.
4. Create a **Dashboard** in Thinger.io and add:
   - A **Gauge widget** pointing to the device's `GasMonitor` resource (`gas_percentage` property, range: `0` to `100`).
   - A **Value widget** pointing to `status` to show normal/danger status strings in real time.
   - A **Time Series Graph** pointing to `raw_data` to log the historic fluctuations.

---

## 🛡️ Git Security Warning

This repository contains hardcoded network passwords and IoT device secret keys. If you make this repository public on GitHub:
- Change the credentials to placeholder values **before** pushing.
- Alternatively, use a private repository.

---

## 📝 License

This project is open-source and available under the [MIT License](LICENSE).
