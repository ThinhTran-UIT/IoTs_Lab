#include <LiquidCrystal.h>              //include the LiquidCrystal library
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);  //define LCD pins (RS, E, D4, D5, D6, D7)

// Create a PulseOximeter object
PulseOximeter pox;

// Time at which the last beat occurred
uint32_t tsLastReport = 0;

// Callback routine is executed when a pulse is detected
void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(9600);

    Serial.print("Initializing pulse oximeter..");

    // Initialize sensor
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
lcd.begin(16, 2); 
lcd.print(" Nuts and Bolts  "); 
lcd.setCursor(0, 1);
delay(5000);
lcd.clear();
 pox.update();

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        lcd.begin(16,2);
        lcd.print("BPM: ");
        lcd.setCursor(0, 1);
        lcd.print(pox.getHeartRate());
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.println("%");

        tsLastReport = millis();
    }

}