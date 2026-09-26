```cpp
#include <DHT.h>

// =====================================================
// THERMOCOLLAR+
// Smart Livestock Monitoring for Early Heat-Stress Detection
//
// Hardware:
// ESP32 DevKit V1
// DHT22 Temperature & Humidity Sensor
// RGB LED
// Buzzer
//
// Decision System:
// Temperature + Humidity → THI → Rule-Based Risk Level
//
// THI Classification:
// THI < 68       → SAFE
// 68 ≤ THI < 79  → CAUTION
// THI ≥ 79       → HIGH
// =====================================================


// =====================================================
// DHT22 SENSOR
// =====================================================

#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// =====================================================
// RGB LED
// =====================================================

#define RED_PIN   25
#define GREEN_PIN 26
#define BLUE_PIN  27


// =====================================================
// BUZZER
// =====================================================

#define BUZZER_PIN 4


// =====================================================
// SENSOR READING INTERVAL
// =====================================================

unsigned long lastRead = 0;

const unsigned long READ_INTERVAL = 2000;


// Prevent the buzzer from repeatedly sounding
// while the system remains in HIGH-risk state.
bool previousHigh = false;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  // Initialize DHT22
  dht.begin();

  // Configure RGB LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Configure buzzer
  pinMode(BUZZER_PIN, OUTPUT);


  // ---------------------------------------------------
  // Initial safe state
  // ---------------------------------------------------

  setRGB(false, true, false);

  digitalWrite(BUZZER_PIN, LOW);


  // ---------------------------------------------------
  // Serial Monitor Startup Information
  // ---------------------------------------------------

  Serial.println();
  Serial.println("========================================");
  Serial.println("          THERMOCOLLAR+");
  Serial.println(" Smart Livestock Heat-Stress Detection");
  Serial.println("========================================");

  Serial.println("ESP32       : READY");
  Serial.println("DHT22       : GPIO 5");
  Serial.println("RED LED     : GPIO 25");
  Serial.println("GREEN LED   : GPIO 26");
  Serial.println("BLUE LED    : GPIO 27");
  Serial.println("BUZZER      : GPIO 4");

  Serial.println("========================================");
  Serial.println();

  delay(1500);
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Read the sensor every 2 seconds
  if (millis() - lastRead >= READ_INTERVAL) {

    lastRead = millis();

    readSensor();
  }
}


// =====================================================
// SENSOR READING + THI CALCULATION
// =====================================================

void readSensor() {

  float humidity = dht.readHumidity();

  float temperature = dht.readTemperature();


  // ---------------------------------------------------
  // SENSOR ERROR CHECK
  // ---------------------------------------------------

  if (isnan(humidity) || isnan(temperature)) {

    Serial.println("ERROR: DHT22 reading failed!");

    // Disable visual and audible alerts
    // until a valid reading is available.
    setRGB(false, false, false);

    digitalWrite(BUZZER_PIN, LOW);

    return;
  }


  // ---------------------------------------------------
  // TEMPERATURE-HUMIDITY INDEX (THI)
  //
  // THI = (1.8T + 32)
  //       - ((0.55 - 0.0055RH)
  //       × (1.8T - 26.8))
  //
  // T  = Temperature in °C
  // RH = Relative Humidity in %
  // ---------------------------------------------------

  float thi =
    (1.8 * temperature + 32.0)
    -
    ((0.55 - 0.0055 * humidity)
    *
    (1.8 * temperature - 26.8));


  // ---------------------------------------------------
  // DISPLAY SENSOR DATA
  // ---------------------------------------------------

  Serial.println("----------------------------------------");

  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("Humidity    : ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("THI         : ");
  Serial.println(thi, 1);


  // ---------------------------------------------------
  // RULE-BASED RISK CLASSIFICATION
  // ---------------------------------------------------

  if (thi < 68.0) {

    safeState();

  }

  else if (thi < 79.0) {

    cautionState();

  }

  else {

    highState();
  }
}


// =====================================================
// SAFE STATE
// THI < 68
// =====================================================

void safeState() {

  Serial.println("Risk        : SAFE");
  Serial.println("RGB         : GREEN");
  Serial.println("Buzzer      : OFF");


  // Green LED
  setRGB(false, true, false);

  // Buzzer OFF
  digitalWrite(BUZZER_PIN, LOW);


  // Reset high-risk state
  previousHigh = false;
}


// =====================================================
// CAUTION STATE
// 68 ≤ THI < 79
// =====================================================

void cautionState() {

  Serial.println("Risk        : CAUTION");
  Serial.println("RGB         : BLUE");
  Serial.println("Buzzer      : OFF");


  // Blue LED
  setRGB(false, false, true);

  // Buzzer OFF
  digitalWrite(BUZZER_PIN, LOW);


  // Reset high-risk state
  previousHigh = false;
}


// =====================================================
// HIGH-RISK STATE
// THI ≥ 79
// =====================================================

void highState() {

  Serial.println("Risk        : HIGH");
  Serial.println("RGB         : RED");
  Serial.println("Buzzer      : ON");


  // Red LED
  setRGB(true, false, false);


  // ---------------------------------------------------
  // Trigger buzzer only when HIGH state is entered.
  // This prevents continuous repeated buzzing.
  // ---------------------------------------------------

  if (!previousHigh) {

    digitalWrite(BUZZER_PIN, HIGH);

    delay(1000);

    digitalWrite(BUZZER_PIN, LOW);

    previousHigh = true;
  }
}


// =====================================================
// RGB LED CONTROL
// =====================================================

void setRGB(bool red, bool green, bool blue) {

  digitalWrite(
    RED_PIN,
    red ? HIGH : LOW
  );

  digitalWrite(
    GREEN_PIN,
    green ? HIGH : LOW
  );

  digitalWrite(
    BLUE_PIN,
    blue ? HIGH : LOW
  );
}
```
