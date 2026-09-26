# 🔧 ThermoCollar+ Hardware Components

ThermoCollar+ is built as a low-cost wearable livestock monitoring prototype using an ESP32, environmental sensing, and local alert mechanisms.

---

## 🧩 Component List

| Component                  | Purpose                                                       |
| -------------------------- | ------------------------------------------------------------- |
| **ESP32 DevKit V1**        | Main controller for sensor processing and risk classification |
| **DHT22**                  | Measures temperature and relative humidity                    |
| **RGB LED**                | Provides immediate visual indication of heat-risk level       |
| **220Ω Resistors**         | Current limiting for RGB LED channels                         |
| **Buzzer**                 | Provides an audible alert during high-risk conditions         |
| **SIM800C GSM Module**     | Optional communication prototype                              |
| **Battery / Power Source** | Provides power to the wearable prototype                      |
| **Collar / Enclosure**     | Holds the electronics as a wearable prototype                 |

---

## 🔌 ESP32 Pin Configuration

The current firmware uses the following GPIO connections:

| Component   | ESP32 GPIO |
| ----------- | ---------: |
| DHT22 Data  |     GPIO 5 |
| RGB — Red   |    GPIO 25 |
| RGB — Green |    GPIO 26 |
| RGB — Blue  |    GPIO 27 |
| Buzzer      |     GPIO 4 |

> Pin assignments correspond to the current `thermocollar_esp32.ino` firmware.

---

## 🌡️ DHT22 Sensor

The DHT22 provides two environmental measurements:

* **Temperature (°C)**
* **Relative Humidity (%)**

The ESP32 reads these values periodically and uses them to calculate the Temperature-Humidity Index (THI).

Current sensor reading interval:

**2 seconds**

---

## 🧠 ESP32 Processing

The ESP32 acts as the main processing unit.

```text
DHT22
  │
  ├── Temperature
  │
  └── Humidity
        │
        ↓
      ESP32
        │
        ↓
   THI Calculation
        │
        ↓
 Rule-Based Classification
        │
   ┌────┼────┐
   ↓    ↓    ↓
 SAFE CAUTION HIGH
```

---

## 💡 RGB LED Status

The RGB LED provides an immediate animal-side indication of the current risk state.

| Status     |        THI | LED   |
| ---------- | ---------: | ----- |
| 🟢 SAFE    |     `< 68` | Green |
| 🔵 CAUTION | `68 – <79` | Blue  |
| 🔴 HIGH    |     `≥ 79` | Red   |

This allows the farmer or caretaker to identify the current condition without opening the dashboard.

---

## 🔊 Buzzer Alert

The buzzer provides an audible alert when the system enters the **HIGH-risk state**.

The current firmware triggers a short buzzer alert when the system enters the high-risk condition rather than continuously sounding the buzzer on every sensor reading.

This helps avoid unnecessary repeated alerts while the condition remains unchanged.

---

## 📡 SIM800C GSM Module

The SIM800C was explored as an optional remote communication component.

The prototype was tested, but network registration was not reliable enough to validate consistent live SMS delivery.

Therefore:

```text
SIM800C
   ↓
Optional Remote Communication
```

is treated as a prototype/future communication path rather than a currently validated live alert channel.

---

## 🔋 Power

The electronics require a suitable power source for portable operation.

The final wearable implementation can be optimized for:

* Battery capacity
* Operating time
* Charging
* Physical protection
* Weather resistance
* Animal comfort

---

## 🐄 Wearable Prototype

The electronics are arranged as a collar-based prototype.

The intended physical arrangement is:

```text
          ┌──────────────────────┐
          │      COLLAR          │
          │                      │
          │  DHT22      RGB LED  │
          │    │           │     │
          │    └─────┬─────┘     │
          │          │           │
          │        ESP32         │
          │          │           │
          │       Buzzer         │
          │          │           │
          │   Battery / Power    │
          └──────────────────────┘
```

The current prototype demonstrates the sensing, processing, and local alert workflow. Further enclosure and power optimization would be required for long-term field deployment.

---

## 🔄 Complete Hardware Flow

```text
       DHT22
    Temperature
    + Humidity
         │
         ↓
       ESP32
         │
         ↓
    THI Calculation
         │
         ↓
  Rule-Based Decision
         │
    ┌────┼────┐
    ↓    ↓    ↓
 GREEN BLUE  RED
    │    │    │
    │    │    └── Buzzer
    │    │
    └────┴──── Local Status
              │
              ↓
       Farmer Dashboard
```

---

## ⚠️ Current Prototype Limitations

The current hardware prototype has the following limitations:

* No physical GPS module is currently integrated.
* Dashboard location data is prototype/simulated GPS data.
* GSM/SMS delivery has not been reliably validated because network registration was inconsistent during testing.
* The current decision system is rule-based THI classification.
* No trained machine-learning model is currently deployed.
* The prototype is intended for monitoring and early warning, not veterinary diagnosis.

---

## 🚀 Hardware Development Opportunities

Future hardware development can include:

* GPS module integration
* More reliable GSM/LTE communication
* Improved battery management
* Weather-resistant enclosure
* Smaller PCB-based implementation
* Low-power operating modes
* Multi-animal deployment
* Additional physiological or behavioral sensors
