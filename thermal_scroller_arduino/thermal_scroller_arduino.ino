#include "Adafruit_Thermal.h"

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setLineHeight(1);
  printer.sleep();      // Tell printer to sleep
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    int nbLines = Serial.parseInt();
    Serial.println(nbLines);

    printer.wake();
    printer.feed(nbLines);
    printer.sleep();   
  }
}
