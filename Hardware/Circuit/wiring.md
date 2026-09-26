# 🔌 ThermoCollar+ Wiring

This document describes the current wiring configuration used by the ThermoCollar+ ESP32 prototype.

---

## 1. ESP32 + DHT22

The DHT22 provides temperature and relative humidity measurements to the ESP32.

| DHT22 Pin | Connection   |
| --------- | ------------ |
| VCC       | 3.3V         |
| DATA      | ESP32 GPIO 5 |
| GND       | GND          |

### Data Flow

```text
DHT22
 ├── Temperature
 └── Humidity
       │
       ↓
   ESP32 GPIO 5
```

---

## 2. ESP32 + RGB LED

The RGB LED provides the local visual indication of the detected heat-risk level.

The current firmware uses three independent ESP32 GPIO outputs.

| RGB Channel | ESP32 GPIO |
| ----------- | ---------: |
| Red         |    GPIO 25 |
| Green       |    GPIO 26 |
| Blue        |    GPIO 27 |

Each LED channel should use an appropriate **current-limiting resistor**.

### Status Mapping

```text
GREEN  → SAFE
BLUE   → CAUTION
RED    → HIGH RISK
```

---

## 3. ESP32 + Buzzer

The buzzer is connected to:

| Buzzer     | ESP32  |
| ---------- | ------ |
| Signal / + | GPIO 4 |
| GND / −    | GND    |

The buzzer is activated when the THI reaches the HIGH-risk range.

The firmware generates a short alert when the system enters the HIGH state.

---

## 4. Overall Connection

```text
                    ┌───────────────┐
                    │    DHT22      │
                    │ Temp + Hum.   │
                    └───────┬───────┘
                            │
                         GPIO 5
                            │
                            ↓
                  ┌─────────────────┐
                  │      ESP32      │
                  │                 │
                  │  THI Calculation│
                  │  Risk Decision  │
                  └────┬────┬───┬───┘
                       │    │   │
                 GPIO25│    │   │GPIO27
                       │    │   │
                       ↓    ↓   ↓
                     RED  GREEN BLUE
                      \     │    /
                       \    │   /
                        RGB LED
                          
                       GPIO 4
                          │
                          ↓
                       Buzzer
```

---

## 5. Pin Summary

| Device  | Signal | ESP32 GPIO |
| ------- | ------ | ---------: |
| DHT22   | DATA   |     GPIO 5 |
| RGB LED | RED    |    GPIO 25 |
| RGB LED | GREEN  |    GPIO 26 |
| RGB LED | BLUE   |    GPIO 27 |
| Buzzer  | Signal |     GPIO 4 |

---

## 6. Power Connections

The sensor and indicator components require suitable power and common ground connections.

```text
ESP32 3.3V ─────→ DHT22 VCC

ESP32 GND ──────→ DHT22 GND
ESP32 GND ──────→ RGB LED common connection
ESP32 GND ──────→ Buzzer GND
```

> The exact power arrangement should match the physical prototype used during testing.

---

## 7. Risk Detection Flow

```text
Temperature
     +
Humidity
     │
     ↓
DHT22
     │
     ↓
ESP32
     │
     ↓
THI Calculation
     │
     ├───────────────┐
     ↓               ↓
  THI < 68       THI ≥ 68
     │               │
     ↓          ┌────┴────┐
    SAFE        ↓         ↓
              CAUTION    HIGH
              68–<79     ≥79
                │         │
              BLUE    RED + BUZZER
```

---

## ⚠️ Wiring Notes

* Use current-limiting resistors for the RGB LED channels.
* Ensure all components share a common ground.
* Verify the RGB LED type and pin arrangement before connecting it.
* Do not connect a component directly to an ESP32 GPIO if its electrical requirements exceed the GPIO's safe operating limits.
* The wiring documented here corresponds to the current prototype firmware.

---

## 🔧 Future Hardware Expansion

The architecture can later be extended with:

```text
                 ┌──────────────┐
                 │     ESP32    │
                 └──────┬───────┘
                        │
          ┌─────────────┼─────────────┐
          ↓             ↓             ↓
       DHT22          GPS          GSM
      Existing       Future       Optional
```

A future version can also include improved power management, a compact PCB, weather-resistant enclosure, and additional livestock stress indicators.

