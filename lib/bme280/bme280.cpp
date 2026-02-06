#include "bme280.h"

// BME280 sensor instance
static Adafruit_BME280 bme;

bool bme280_init(void) {
    bool status = bme.begin(0x76);  // Default I2C address (0x76)
    
    if (!status) {
        // Try alternative address
        status = bme.begin(0x77);
    }
    
    if (status) {
        Serial.println("BME280 sensor initialized successfully");
    } else {
        Serial.println("ERROR: Could not find BME280 sensor!");
    }
    
    return status;
}

bool bme280_read(bme280_data_t* data) {
    if (data == NULL) {
        return false;
    }
    
    data->temperature = bme.readTemperature();
    data->humidity = bme.readHumidity();
    data->pressure = bme.readPressure() / 100.0F;  // Convert Pa to hPa
    data->altitude = bme.readAltitude(1013.25);    // Sea level pressure in hPa
    
    // Check if readings are valid (BME280 returns NaN on error)
    if (isnan(data->temperature) || isnan(data->humidity) || 
        isnan(data->pressure) || isnan(data->altitude)) {
        return false;
    }
    
    return true;
}
