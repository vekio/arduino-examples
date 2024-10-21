/*
 * ==================================================
 * File Name:      dht11_lcd.ino
 * Description:    Displays temperature, humidity, and heat index using a DHT11 sensor and an LCD.
 * Author:         Alberto Castañeiras
 * Creation Date:  2024-10-21
 * Version:        1.0
 * ==================================================
 * Hardware:       Arduino Nano, DHT11 sensor, LCD with I2C interface
 * Dependencies:   DHT library, LiquidCrystal_I2C library
 * Notes:
 * ==================================================
 * DHT11 Sensor:
 *   D2 ==> Data Pin
 * LCD:
 *   A4 ==> SDA (I2C Data Line)
 *   A5 ==> SCL (I2C Clock Line)
 * ==================================================
 */

#include <DHT.h>               // Library for DHT sensor
#include <Wire.h>              // I2C communication library
#include <LiquidCrystal_I2C.h> // LCD library for I2C

#define DHTPIN 2      // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // Specify the type of DHT sensor

// Initialize the DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD, address 0x27, with 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(115200);

    dht.begin(); // Start the DHT sensor

    // Initialize the LCD and turn on the backlight
    lcd.init();
    lcd.backlight();
}

void loop()
{
    // Wait a few seconds between measurements
    delay(2000);

    lcd.clear();

    float h = dht.readHumidity();    // Read humidity value
    float t = dht.readTemperature(); // Read temperature in Celsius

    // Check if any reads failed
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    // Compute the heat index in Celsius (isFahrenheit = false)
    int hic = dht.computeHeatIndex(t, h, false);

    // Print the results to the Serial Monitor
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C  Heat Index: "));
    Serial.print(hic);
    Serial.println(F("°C"));

    // Display the readings on the LCD screen
    lcd.setCursor(0, 0);
    lcd.print(F("Humidity: "));
    lcd.print(h);
    lcd.print(F("%"));
    lcd.setCursor(0, 1);
    lcd.print(F("Temp "));
    lcd.print(t);
    lcd.print(F("C ("));
    lcd.print(hic);
    lcd.print(F(")"));
}
