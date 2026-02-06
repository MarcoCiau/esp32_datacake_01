#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "credentials.h"

#ifndef USE_SIMULATED_DEVICE
#include "bme280.h"
#endif

#define HTTP_POST_INTERVAL_MS (10000UL)

void setup() {
  Serial.begin(115200);
  
#ifdef USE_SIMULATED_DEVICE
  Serial.println("Using simulated sensor data");
#else
  Serial.println("Initializing BME280 sensor...");
  if (!bme280_init()) {
    Serial.println("WARNING: BME280 initialization failed. Check wiring!");
  }
#endif

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(DATACAKE_SERVER_URL);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDoc;
    jsonDoc["device"] = DATACAKE_DEVICE_ID;
    
    bool dataReady = false;
    
#ifdef USE_SIMULATED_DEVICE
    // Simulated sensor data using random()
    jsonDoc["temperature"] = random(200, 350) / 10.0;  // 20.0 to 35.0 °C
    jsonDoc["humidity"]    = random(300, 900) / 10.0;  // 30.0% to 90.0%
    jsonDoc["pressure"]    = random(98000, 102000) / 100.0;  // 980.0 to 1020.0 hPa
    jsonDoc["altitude"]    = random(400, 600) / 10.0;  // 40.0 to 60.0 meters
    dataReady = true;
#else
    // Read data from BME280 sensor
    bme280_data_t sensorData;
    if (bme280_read(&sensorData)) {
      jsonDoc["temperature"] = sensorData.temperature;
      jsonDoc["humidity"]    = sensorData.humidity;
      jsonDoc["pressure"]    = sensorData.pressure;
      jsonDoc["altitude"]    = sensorData.altitude;
      dataReady = true;
    } else {
      Serial.println("ERROR: Failed to read BME280 sensor data!");
    }
#endif

    if (dataReady) {
      String requestBody;
      serializeJson(jsonDoc, requestBody);
      Serial.println("\n-----------------------------");
      Serial.println("Sending JSON to Datacake:");
      Serial.println(requestBody);
      Serial.println("-----------------------------");
      int httpResponseCode = http.POST(requestBody);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
    }

    http.end();
  }

  delay(HTTP_POST_INTERVAL_MS); // Send data every 60 seconds
}