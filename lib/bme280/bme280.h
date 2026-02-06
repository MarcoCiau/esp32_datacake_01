#ifndef BME280_H
#define BME280_H

#include <Wire.h>
#include <Adafruit_BME280.h>

// BME280 sensor data structure
typedef struct {
    float temperature;  // °C
    float humidity;     // %
    float pressure;     // hPa
    float altitude;     // meters
} bme280_data_t;

// Initialize BME280 sensor
// Returns true if initialization successful, false otherwise
bool bme280_init(void);

// Read sensor data
// Returns true if read successful, false otherwise
bool bme280_read(bme280_data_t* data);

#endif // BME280_H
