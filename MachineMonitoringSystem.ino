#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int sensorPins[] = {9, 10, 11, 12, 13}; 
const int buzzerPin = 8;
const int ledPins[] = {14, 15, 16, 17, 18}; 
bool sensorValues[5];
const char* machineIDs[] = {"MQASTC01", "MQASTC02", "MQASTC03", "MQASTC04", "MQASTC05"};

void setup() {
  lcd.begin(16, 2); 
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
  lcd.clear();
  lcd.print("No Alert"); 
}

void loop() {
  bool alert = false; 

  for (int i = 0; i < 5; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(sensorValues[i]);

    if (sensorValues[i] == HIGH) { 
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPins[i], HIGH);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Alert:Machine ID");
      lcd.setCursor(0, 1); 
      lcd.print(machineIDs[i]);
      delay(1000); 
      alert = true; 
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

  if (!alert) {
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
    lcd.print("No Alert");
  }

  delay(500); // Read delay
}
