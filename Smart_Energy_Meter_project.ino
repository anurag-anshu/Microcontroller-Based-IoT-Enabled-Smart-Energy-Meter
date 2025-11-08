#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>  
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>    // For Wi-Fi
#include "ThingSpeak.h"     // For ThingSpeak

// ================== Pin Configuration ==================
#define PZEM_RX_PIN D6  // PZEM TX -> NodeMCU D6 (RX)
#define PZEM_TX_PIN D7  // PZEM RX -> NodeMCU D7 (TX)

// LCD setup
#define LCD_ADDR 0x27
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

// PZEM over SoftwareSerial
SoftwareSerial pzemSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSerial);

// ================== Wi-Fi + ThingSpeak Setup ==================
const char* ssid = "OnePlus 11R";        // <-- Wifi name
const char* password = "anuragjha08032005"; // <-- Wifi Password
unsigned long myChannelNumber = 3144992; // Channel Number 
const char* myWriteAPIKey = "G4IEMJZIYAMEL8SA";     // <-- API Key

WiFiClient client;

unsigned long lastRead = 0;
const unsigned long readInterval = 20000; // 20 sec (ThingSpeak limit)

// ==============================================================
void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL for LCD

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Energy");
  lcd.setCursor(0, 1);
  lcd.print("Meter Starting...");
  delay(1500);
  lcd.clear();

  // Wi-Fi Connection
  WiFi.begin(ssid, password);
  lcd.print("WiFi Connecting");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  lcd.clear();
  lcd.print("WiFi Connected!");

  ThingSpeak.begin(client);  // Initialize ThingSpeak
  delay(2000);
  lcd.clear();
}

// ==============================================================
void loop() {
  if (millis() - lastRead >= readInterval) {
    lastRead = millis();

    float voltage = pzem.voltage();
    float current = pzem.current();
    float power   = pzem.power();
    float energy  = pzem.energy();
    float freq    = pzem.frequency();
    float pf      = pzem.pf();

    // Print readings on Serial Monitor
    Serial.println("----------------------------");
    Serial.printf("Voltage: %.2f V\n", voltage);
    Serial.printf("Current: %.3f A\n", current);
    Serial.printf("Power: %.2f W\n", power);
    Serial.printf("Energy: %.3f kWh\n", energy);
    Serial.printf("Frequency: %.2f Hz\n", freq);
    Serial.printf("PowerFactor: %.2f\n", pf);
    Serial.println("----------------------------\n");

    // Print readings on LCD Display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.print(voltage, 1);
    lcd.print(" I:");
    lcd.print(current, 2);
    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(power, 0);
    lcd.print("W");

    // Send data to ThingSpeak
    ThingSpeak.setField(1, voltage);
    ThingSpeak.setField(2, current);
    ThingSpeak.setField(3, power);
    ThingSpeak.setField(4, energy);
    ThingSpeak.setField(5, freq);
    ThingSpeak.setField(6, pf);

    int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (statusCode == 200) {
      Serial.println("Data successfully sent to ThingSpeak!");
      lcd.setCursor(9, 1);
      lcd.print("Sent");
    } else {
      Serial.print("ThingSpeak Error: ");
      Serial.println(statusCode);
      lcd.setCursor(9, 1);
      lcd.print("Err");
    }
  }
}