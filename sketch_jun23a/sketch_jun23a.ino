#define THINGER_SERIAL_DEBUG

#include <WiFi.h>
#include <ThingerESP32.h>

// Thinger.io Credentials
#define USERNAME     "YOUR_THINGER_USERNAME"
#define DEVICE_ID    "YOUR_DEVICE_ID"
#define DEVICE_CRED  "YOUR_DEVICE_CREDENTIALS"

// WiFi Credentials
#define SSID         "YOUR_WIFI_SSID"
#define SSID_PASSWORD "YOUR_WIFI_PASSWORD"


ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CRED);

// Hardware Pins
const int MQ2_PIN = 34;    // Analog pin for MQ2 Sensor
const int RED_LED = 25;    // Red LED Pin for Alert
const int GREEN_LED = 26;  // Green LED Pin for Normal Status

// Calibration & Thresholds
const int GAS_THRESHOLD_PERCENT = 30; // Threshold percentage for alert status

void setup() {
  Serial.begin(115200);

  // Initialize LED Pins as Outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Default state: turn both off initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // Initialize WiFi and Thinger.io
  thing.add_wifi(SSID, SSID_PASSWORD);

  // Define the Thinger.io resource
  thing["GasMonitor"] >> [](pson& out){
    // Noise reduction: average 10 readings for a stable dashboard output
    int rawValue = 0;
    for(int i = 0; i < 10; i++) {
      rawValue += analogRead(MQ2_PIN);
      delay(5);
    }
    rawValue /= 10;
    
    // Map the 12-bit ADC value (0-4095) to a rough percentage (0-100%)
    float gasPercent = (float(rawValue) / 4095.0) * 100.0;
    
    // Determine status text and control hardware LEDs
    String statusText;
    if (gasPercent > GAS_THRESHOLD_PERCENT) {
      statusText = "DANGER: Gas Leak Detected!";
      digitalWrite(RED_LED, HIGH);   // Turn ON Red Alert
      digitalWrite(GREEN_LED, LOW);  // Turn OFF Green Safe
    } else {
      statusText = "Status: Normal";
      digitalWrite(RED_LED, LOW);    // Turn OFF Red Alert
      digitalWrite(GREEN_LED, HIGH); // Turn ON Green Safe
    }

    // Output variables to Thinger.io dashboard
    out["raw_data"] = rawValue;
    out["gas_percentage"] = gasPercent;
    out["status"] = statusText;
  };
}

void loop() {
  thing.handle();
}