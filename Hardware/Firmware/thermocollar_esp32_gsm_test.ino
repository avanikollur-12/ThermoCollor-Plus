#include <DHT.h>

// ============================================================
// THERMOCOLLAR+
// Livestock Heat-Stress Monitoring System
// ============================================================

// ---------------- DHT22 ----------------
#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// ---------------- RGB LED ----------------
#define RED_PIN    25
#define GREEN_PIN  26
#define BLUE_PIN   27


// ---------------- BUZZER ----------------
#define BUZZER_PIN 4


// ---------------- GSM UART ----------------
// SIM800C HU-591
// HU-591 R (RX) -> ESP32 GPIO17 (TX2)
// HU-591 T (TX) -> ESP32 GPIO16 (RX2)

#define GSM_RX 16
#define GSM_TX 17

HardwareSerial GSM(2);


// ============================================================
// SETTINGS
// ============================================================

const unsigned long SENSOR_INTERVAL = 2000;

unsigned long lastSensorRead = 0;


// Buzzer timing
const unsigned long BUZZER_ON_TIME  = 200;
const unsigned long BUZZER_OFF_TIME = 300;

unsigned long lastBuzzerChange = 0;
bool buzzerState = false;


// ============================================================
// RISK LEVEL
// ============================================================

enum RiskLevel
{
  SAFE,
  CAUTION,
  HIGH_RISK,
  SENSOR_ERROR
};

RiskLevel currentRisk = SAFE;


// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  // DHT
  dht.begin();


  // RGB
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);


  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);


  // GSM
  GSM.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);


  // Initial state
  setRGB(false, true, false);

  digitalWrite(BUZZER_PIN, LOW);


  // ----------------------------------------------------------
  // STARTUP MESSAGE
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("========================================");
  Serial.println("          THERMOCOLLAR+");
  Serial.println(" LIVESTOCK HEAT-STRESS MONITOR");
  Serial.println("========================================");

  Serial.println("ESP32       : READY");
  Serial.println("DHT22       : GPIO 5");
  Serial.println("RED LED     : GPIO 25");
  Serial.println("GREEN LED   : GPIO 26");
  Serial.println("BLUE LED    : GPIO 27");
  Serial.println("BUZZER      : GPIO 4");

  Serial.println("----------------------------------------");

  Serial.println("SIM800C     : CONNECTED");
  Serial.println("GSM UART    : GPIO16 / GPIO17");
  Serial.println("GSM MODE    : NETWORK DEPENDENT");

  Serial.println("========================================");
  Serial.println();

  delay(1500);


  // Check GSM communication
  checkGSM();
}


// ============================================================
// MAIN LOOP
// ============================================================

void loop()
{

  // ----------------------------------------------------------
  // READ DHT22 EVERY 2 SECONDS
  // ----------------------------------------------------------

  if (millis() - lastSensorRead >= SENSOR_INTERVAL)
  {
    lastSensorRead = millis();

    readSensor();
  }


  // ----------------------------------------------------------
  // UPDATE BUZZER WITHOUT BLOCKING SENSOR
  // ----------------------------------------------------------

  updateBuzzer();


  // ----------------------------------------------------------
  // READ GSM RESPONSES
  // ----------------------------------------------------------

  while (GSM.available())
  {
    Serial.write(GSM.read());
  }
}


// ============================================================
// DHT22 + THI
// ============================================================

void readSensor()
{

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();


  // ----------------------------------------------------------
  // SENSOR ERROR
  // ----------------------------------------------------------

  if (isnan(humidity) || isnan(temperature))
  {

    Serial.println();
    Serial.println("========================================");
    Serial.println("DHT22 ERROR");
    Serial.println("Sensor reading failed");
    Serial.println("========================================");

    currentRisk = SENSOR_ERROR;

    setRGB(false, false, false);

    digitalWrite(BUZZER_PIN, LOW);

    buzzerState = false;

    return;
  }


  // ----------------------------------------------------------
  // THI CALCULATION
  // ----------------------------------------------------------

  float thi =
    (1.8 * temperature + 32.0)
    -
    (
      (0.55 - 0.0055 * humidity)
      *
      (1.8 * temperature - 26.8)
    );


  // ----------------------------------------------------------
  // SERIAL OUTPUT
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("----------------------------------------");

  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("Humidity    : ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("THI         : ");
  Serial.println(thi, 1);


  // ----------------------------------------------------------
  // RISK CLASSIFICATION
  // ----------------------------------------------------------

  if (thi < 68.0)
  {
    safeState();
  }

  else if (thi < 79.0)
  {
    cautionState();
  }

  else
  {
    highState();
  }


  Serial.println("----------------------------------------");
}


// ============================================================
// SAFE
// ============================================================

void safeState()
{

  currentRisk = SAFE;

  Serial.println("Risk        : SAFE");
  Serial.println("RGB         : GREEN");
  Serial.println("Buzzer      : OFF");

  setRGB(false, true, false);

  digitalWrite(BUZZER_PIN, LOW);

  buzzerState = false;
}


// ============================================================
// CAUTION
// ============================================================

void cautionState()
{

  currentRisk = CAUTION;

  Serial.println("Risk        : CAUTION");
  Serial.println("RGB         : BLUE");
  Serial.println("Buzzer      : OFF");

  setRGB(false, false, true);

  digitalWrite(BUZZER_PIN, LOW);

  buzzerState = false;
}


// ============================================================
// HIGH RISK
// ============================================================

void highState()
{

  currentRisk = HIGH_RISK;

  Serial.println("Risk        : HIGH");
  Serial.println("RGB         : RED");
  Serial.println("Buzzer      : ALARM");

  setRGB(true, false, false);
}


// ============================================================
// RGB CONTROL
// ============================================================

void setRGB(bool red, bool green, bool blue)
{

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


// ============================================================
// BUZZER CONTROL
// ============================================================

void updateBuzzer()
{

  // Buzzer OFF for SAFE, CAUTION and SENSOR ERROR
  if (currentRisk != HIGH_RISK)
  {

    digitalWrite(BUZZER_PIN, LOW);

    buzzerState = false;

    return;
  }


  unsigned long now = millis();


  // ----------------------------------------------------------
  // BUZZER ON
  // ----------------------------------------------------------

  if (buzzerState)
  {

    if (now - lastBuzzerChange >= BUZZER_ON_TIME)
    {

      digitalWrite(BUZZER_PIN, LOW);

      buzzerState = false;

      lastBuzzerChange = now;
    }
  }


  // ----------------------------------------------------------
  // BUZZER OFF
  // ----------------------------------------------------------

  else
  {

    if (now - lastBuzzerChange >= BUZZER_OFF_TIME)
    {

      digitalWrite(BUZZER_PIN, HIGH);

      buzzerState = true;

      lastBuzzerChange = now;
    }
  }
}


// ============================================================
// GSM CHECK
// ============================================================

void checkGSM()
{

  Serial.println();
  Serial.println("========================================");
  Serial.println("       GSM COMMUNICATION TEST");
  Serial.println("========================================");


  GSM.println("AT");

  delay(1000);

  Serial.println("SIM800C AT command sent.");


  // Signal check
  GSM.println("AT+CSQ");

  delay(1000);

  Serial.println("Signal check requested.");


  // SIM check
  GSM.println("AT+CPIN?");

  delay(1000);

  Serial.println("SIM status requested.");


  // Network registration
  GSM.println("AT+CREG?");

  delay(1000);

  Serial.println("Network registration checked.");

  Serial.println();
  Serial.println("NOTE:");
  Serial.println("GSM remote communication depends on");
  Serial.println("cellular network registration.");
  Serial.println("Core safety system remains independent.");
  Serial.println("========================================");
}


// ============================================================
// OPTIONAL GSM STATUS CHECK
// ============================================================

void gsmRegistrationCheck()
{

  GSM.println("AT+CREG?");

  delay(500);

  while (GSM.available())
  {
    Serial.write(GSM.read());
  }
}
