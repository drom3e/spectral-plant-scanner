/*
  Spectral Plant Scanner (reference example)
  ESP32 + Adafruit AS7341 spectral sensor

  Reads reflected light from a leaf, computes a simple
  red/NIR vegetation index, and flags possible plant stress.

  Wiring (I2C):
    AS7341 VIN -> 3.3V
    AS7341 GND -> GND
    AS7341 SDA -> GPIO 21
    AS7341 SCL -> GPIO 22

  Library: Adafruit AS7341 (install via Library Manager)
*/

#include <Wire.h>
#include <Adafruit_AS7341.h>

Adafruit_AS7341 as7341;

// Tune these by scanning known healthy and stressed leaves
const float HEALTHY_INDEX_MIN = 0.45;  // below this = flag as stressed
const int   SAMPLES           = 5;     // readings averaged per scan

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin(21, 22);

  if (!as7341.begin()) {
    Serial.println("AS7341 not found. Check wiring.");
    while (true) delay(10);
  }

  // Integration time = (ATIME+1) * (ASTEP+1) * 2.78us
  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_64X);

  // Onboard LED for consistent lighting
  as7341.setLEDCurrent(20);  // mA
  as7341.enableLED(true);

  Serial.println("Scanner ready. Hold sensor against a leaf.");
}

float readIndex() {
  if (!as7341.readAllChannels()) {
    return NAN;
  }

  float red = as7341.getChannel(AS7341_CHANNEL_680nm_F8);
  float nir = as7341.getChannel(AS7341_CHANNEL_NIR);

  if ((nir + red) == 0) return NAN;

  // NDVI-style index: healthy leaves absorb red and reflect NIR
  return (nir - red) / (nir + red);
}

void loop() {
  float total = 0;
  int valid = 0;

  for (int i = 0; i < SAMPLES; i++) {
    float v = readIndex();
    if (!isnan(v)) {
      total += v;
      valid++;
    }
    delay(100);
  }

  if (valid == 0) {
    Serial.println("Read error.");
    delay(1000);
    return;
  }

  float index = total / valid;

  Serial.print("Vegetation index: ");
  Serial.print(index, 3);
  Serial.print("  ->  ");
  Serial.println(index < HEALTHY_INDEX_MIN ? "POSSIBLE STRESS" : "HEALTHY");

  // TODO: send result to phone app (Bluetooth/Wi-Fi)

  delay(1000);
}
