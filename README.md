# 🐄 ThermoCollar+

### Smart Livestock Monitoring for Early Heat-Stress Detection

**NIRMAAN 2026 – AgriTech Track**
**Team Triple Espresso**
**Nitte Meenakshi Institute of Technology (NMIT), Bengaluru**

---

## 🌱 Overview

**ThermoCollar+** is a wearable livestock monitoring prototype designed to help farmers identify potential heat-stress conditions in cattle at an early stage.

The system continuously monitors **temperature and humidity** using a DHT22 sensor connected to an ESP32. These readings are converted into a **Temperature-Humidity Index (THI)**, which is then used by a rule-based decision system to classify the animal's heat-risk level.

The collar provides an immediate **RGB LED and buzzer alert**, while a **Streamlit dashboard** provides a broader view of animal and herd conditions.

### Core workflow

```text
Temperature + Humidity
          ↓
        DHT22
          ↓
        ESP32
          ↓
      THI Calculation
          ↓
   Rule-Based Classification
          ↓
 ┌────────┴─────────┐
 ↓                  ↓
Local Alert     Farmer Dashboard
RGB + Buzzer    Streamlit Interface
```

---

## 🎯 Problem

Heat stress can develop before farmers notice obvious physical symptoms. Delayed detection can affect livestock health and productivity, while small and marginal farmers may not have access to expensive monitoring systems.

ThermoCollar+ aims to provide a **low-cost, practical early-warning mechanism** that connects animal-side sensing with farmer-oriented monitoring.

---

## 💡 Solution

ThermoCollar+ combines:

* 🌡️ Temperature monitoring
* 💧 Humidity monitoring
* 📊 THI-based heat-risk classification
* 💡 RGB LED status indication
* 🔊 Local buzzer alerts
* 🖥️ Streamlit farmer dashboard
* 🐄 Herd-level visualization
* 🗺️ Prototype/simulated animal location visualization
* 🌐 English and Kannada dashboard support
* 📡 Optional GSM-based communication

The system follows a simple workflow:

**Detect → Alert → Locate → Respond → Recover**

---

## 🧠 Heat-Risk Detection

The prototype uses the **Temperature-Humidity Index (THI)** to estimate heat-risk conditions.

### THI Formula

```text
THI = (1.8T + 32)
      - ((0.55 - 0.0055RH)
      × (1.8T - 26.8))
```

Where:

* `T` = Temperature in °C
* `RH` = Relative Humidity %

### Prototype Classification

| THI Range     | Status       | Local Indication |
| ------------- | ------------ | ---------------- |
| THI < 68      | 🟢 Safe      | Green LED        |
| 68 ≤ THI < 79 | 🔵 Caution   | Blue LED         |
| THI ≥ 79      | 🔴 High Risk | Red LED + Buzzer |

The current prototype uses **rule-based THI classification**. It does **not** use a trained machine-learning model.

---

## 🔧 Hardware

The current prototype consists of:

* **ESP32 DevKit V1**
* **DHT22 temperature & humidity sensor**
* **RGB LED**
* **220Ω resistors**
* **Buzzer**
* **SIM800C GSM module** —
