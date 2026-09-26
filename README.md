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
* **SIM800C GSM module** — optional communication prototype
* **Battery / power source**
* **Livestock collar / enclosure**

### Hardware Architecture

```text
             ┌──────────────┐
             │    DHT22     │
             │ Temp + Hum.  │
             └──────┬───────┘
                    │
                    ↓
             ┌──────────────┐
             │    ESP32     │
             │ THI + Rules  │
             └──────┬───────┘
                    │
          ┌─────────┼─────────┐
          ↓         ↓         ↓
       RGB LED   Buzzer    SIM800C
          │         │         │
          ↓         ↓         ↓
       Local     Local     Optional
       Status    Alert    Communication
                    │
                    ↓
             Farmer Dashboard
```

---

## 🖥️ Farmer Dashboard

The ThermoCollar+ Streamlit dashboard provides a centralized view of livestock conditions.

The prototype dashboard includes:

* Herd overview
* Animal profiles
* Temperature
* Humidity
* THI
* Heat-risk status
* RGB status
* Buzzer status
* Communication status
* Alerts
* Recommended actions
* Herd map visualization
* English / Kannada interface

The dashboard is designed to help a farmer move from **raw sensor readings to an actionable response**.

---

## 🗺️ Herd Location Visualization

The dashboard includes a map-based visualization for monitoring individual animals.

Example animals include:

* Kaveri — C001
* Ganga — C002
* Lakshmi — C003
* Radha — C004
* Nandi — C005

> **Important:** GPS locations shown in the current dashboard are **prototype/simulated GPS data**. The present hardware prototype does not contain a GPS module.

---

## 🚨 Alert Workflow

When the system detects a high-risk THI condition:

```text
1. DETECT
   High heat-risk condition identified

        ↓

2. ALERT
   Red LED + buzzer + dashboard alert

        ↓

3. LOCATE
   Identify the animal on the herd map

        ↓

4. RESPOND
   Provide water
   Move animal to shade
   Begin cooling

        ↓

5. RECOVER
   Continue monitoring until conditions
   return to the safe range
```

---

## 📡 GSM / SMS Communication

A **SIM800C GSM module** was explored as an optional remote communication feature.

The prototype was tested, but network registration was not reliable enough to claim successful live SMS delivery.

Therefore, GSM/SMS is currently considered an **optional prototype feature**, rather than a validated live communication channel.

Future deployment can integrate:

* Reliable GSM/SMS alerts
* Cloud push notifications
* Farm management platforms
* Veterinary notifications

---

## 🧪 Prototype Testing

The prototype was tested using controlled environmental conditions and live sensor readings.

### Test Scenarios

| Test | Condition                      | Expected Result       |
| ---- | ------------------------------ | --------------------- |
| 01   | Normal temperature/humidity    | 🟢 Safe               |
| 02   | Increased temperature/humidity | 🔵 Caution            |
| 03   | High heat simulation           | 🔴 High Risk + Buzzer |

Testing focuses on validating the complete local detection and alert workflow.

---

## 🏗️ Technology Stack

### Hardware

```text
ESP32
DHT22
RGB LED
Buzzer
SIM800C
```

### Software

```text
Arduino / ESP32 Firmware
Python
Streamlit
THI Rule Engine
Interactive Map Visualization
```

---

## 📁 Project Structure

```text
ThermoCollar-Plus/
│
├── hardware/
│   ├── firmware/
│   ├── circuit/
│   └── components.md
│
├── dashboard/
│   ├── app.py
│   └── requirements.txt
│
├── docs/
│   ├── architecture/
│   ├── testing/
│   └── presentation/
│
├── images/
│   ├── prototype/
│   ├── dashboard/
│   └── diagrams/
│
├── data/
│   └── sample/
│
├── README.md
└── LICENSE
```

---

## 🚀 Future Scope

The prototype can be extended with:

* Real GPS hardware integration
* Reliable GSM/SMS communication
* Historical THI data storage
* Field-data-based ML model development
* Panting/acoustic stress detection
* Multi-collar farm deployment
* Veterinary alert integration
* Cloud-based analytics
* Dairy cooperative deployment

---

## 👥 Team

### Team Triple Espresso

**Avani Kollur** — Team Leader
**Manya M Poojari** — Team Member
**Ananya S K** — Team Member

**Nitte Meenakshi Institute of Technology (NMIT), Bengaluru**

---

## 🏆 Hackathon

**NIRMAAN 2026 — AgriTech Track**

**Project:** ThermoCollar+
**Tagline:** *Smart Livestock Monitoring for Early Heat-Stress Detection*

---

## ⚠️ Prototype Disclaimer

ThermoCollar+ is a working engineering prototype developed for the NIRMAAN 2026 hackathon.

The current system uses **THI-based rule classification** and does not contain a trained machine-learning model.

Location information displayed by the dashboard is **prototype/simulated GPS data**, as the current collar does not contain a GPS module.

GSM/SMS communication is an optional feature under development and successful live SMS delivery has not been established due to unreliable network registration during prototype testing.

The system is intended as an **early-warning and monitoring prototype**, not as a veterinary diagnostic system.

---

## 💚 ThermoCollar+

> **Turning invisible heat stress into an actionable warning — before it becomes an emergency.**
