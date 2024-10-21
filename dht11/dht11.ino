/*
 * ==================================================
 * File Name:      dht11.ino
 * Description:    Displays temperature, humidity, and heat index using a DHT11 sensor.
 * Author:         Alberto Castañeiras
 * Creation Date:  2024-10-20
 * Version:        1.0
 * ==================================================
 * Hardware:       Arduino Nano, DHT11 sensor
 * Dependencies:   DHT library
 * Notes:
 * ==================================================
 * DHT11 Sensor:
 *   D2 ==> Data Pin
 * ==================================================
 */
#include "DHT.h"

#define DHTPIN 2      // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // Specify the type of DHT sensor

// Initialize the DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);

    dht.begin(); // Start the DHT sensor
}

void loop()
{
    // Wait a few seconds between measurements
    delay(2000);

    float h = dht.readHumidity();    // Read humidity
    float t = dht.readTemperature(); // Read temperature in Celsius by default

    // Check if any reads failed
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    // Compute the heat index in Celsius (isFahrenheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    // Print the results to the Serial Monitor
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C  Heat Index: "));
    Serial.print(hic);
    Serial.println(F("°C"));
}
