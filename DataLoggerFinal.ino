#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>

#define DHTPIN 2
#define PIN_SPI_CS 4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
File myFile;

void setup() {
  Serial.begin(9600);

  if (!SD.begin(PIN_SPI_CS)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }

  myFile = SD.open("arduino.txt", FILE_WRITE);

  if (myFile) {
    myFile.println("DataLogger Humidity dan Temperatur"); // write a line to Arduino
    myFile.println("  Hum     Temp"); // write another  line to Arduino
    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }
    Serial.println(F("SD CARD INITIALIZED."));

  dht.begin();

  lcd.init();
  lcd.backlight();

}

void loop() {

  delay(1000);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  myFile = SD.open("arduino.txt", FILE_WRITE);

  if (myFile) {
    myFile.print("  "); // write a line to Arduino
    myFile.print(hum); // write another  line to Arduino
    myFile.print("    "); // write another  line to Arduino   
    myFile.println(temp); // write another  line to Arduino  
    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }

  tampilLCDTemp(temp);
  tampilLCDHum(hum);

}

void tampilLCDTemp(float temp) {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temp, 2);
  lcd.setCursor(15, 0);
  lcd.print("C");
}

void tampilLCDHum(float hum) {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: ");
  lcd.print(hum, 0);
  lcd.setCursor(15, 1);
  lcd.print("%");
}