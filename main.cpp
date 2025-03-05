#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP085 bmp;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    if (!bmp.begin()) {
        Serial.println("no sensor connected, process halted");
        digitalWrite(LED_BUILTIN, HIGH);
    }
        while (1);
}

void loop()
{

}