#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP085 bmp;

const int EEPROM_SIZE = 1024;
const int BYTES_PER_ENTRY = 6;
const int MAX_ENTRIES = EEPROM_SIZE / BYTES_PER_ENTRY;

int entryCount = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    if (!bmp.begin()) {
        Serial.println("no sensor connected");
        digitalWrite(LED_BUILTIN, HIGH);
        while (1);
    }
        
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,     
                  Adafruit_BMP280::SAMPLING_X16,    
                  Adafruit_BMP280::FILTER_X16,     
                  Adafruit_BMP280::STANDBY_MS_500); 
}
void loop()
{
    if (entryCount >= MAX_ENTRIES) {
    Serial.println("max");
    while (1); 
    }
  
  int16_t pressure = (int16_t)bmp.readPressure(); 
  int16_t altitude = (int16_t)bmp.readAltitude(1013.25); 
  int16_t temperature = (int16_t)(bmp.readTemperature() * 100); 
  
  int address = entryCount * BYTES_PER_ENTRY;
  
  
  EEPROM.update(address, pressure & 0xFF);
  EEPROM.update(address + 1, (pressure >> 8) & 0xFF);
  EEPROM.update(address + 2, altitude & 0xFF);
  EEPROM.update(address + 3, (altitude >> 8) & 0xFF);
  EEPROM.update(address + 4, temperature & 0xFF);
  EEPROM.update(address + 5, (temperature >> 8) & 0xFF);
  

  entryCount++;
  

  Serial.print(entryCount);
  Serial.print("********************")
  Serial.print(pressure);
  Serial.print(altitude);
  Serial.print(temperature / 100.0);
  Serial.print("====================")


  delay(1000);
}
  
  

