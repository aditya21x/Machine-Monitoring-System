#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int sensorPins[] = {9, 10, 11, 12, 13}; // Digital input pins
const int buzzerPin = 8;
const int ledPins[] = {14, 15, 16, 17, 18}; // LED pins corresponding to each machine
bool sensorValues[5];
const char* machineIDs[] = {"MQASTC01", "MQASTC02", "MQASTC03", "MQASTC04", "MQASTC05"};

void setup() {
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
  lcd.clear();
  lcd.print("No Alert"); // Initial display
}

void loop() {
  bool alert = false; // Variable to track if any alert is triggered

  for (int i = 0; i < 5; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(sensorValues[i]);

    if (sensorValues[i] == HIGH) { // Check if the digital input is HIGH
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPins[i], HIGH);
      lcd.clear();
      lcd.setCursor(0, 0); // Set cursor to the beginning of the first row
      lcd.print("Alert:Machine ID");
      lcd.setCursor(0, 1); // Set cursor to the beginning of the second row
      lcd.print(machineIDs[i]);
      delay(1000); // Alert delay
      alert = true; // An alert is present
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
