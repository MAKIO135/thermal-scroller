#include "Adafruit_Thermal.h"

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

int choice = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setLineHeight(1);
  printer.setSize('L');
  printer.sleep();      // Tell printer to sleep
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    int nbLines = Serial.parseInt();
    Serial.println(nbLines);

    printer.wake();

    if(nbLines > 40) {
      if(choice == 0) {
        printer.println(F("Bon, encore 10")); 
        printer.println(F("minutes de plus")); 
        printer.println(F("et je m'y mets.")); 
      }
      else if(choice == 1) {
        printer.println(F("Allez, juste")); 
        printer.println(F("quelques minutes")); 
        printer.println(F("de plus.")); 
      }
      else if(choice == 2) {
        printer.println(F("5 minutes,")); 
        printer.println(F("c'est rien,")); 
        printer.println(F("non ?")); 
      }
      else if(choice == 3) {
        printer.println(F("J'arriverai un")); 
        printer.println(F("peu en retard")); 
        printer.println(F("pour le diner,")); 
        printer.println(F("pas grave.")); 
      }
      else if(choice == 4) {
        printer.println(F("Moi accro a")); 
        printer.println(F("Instagram ? Pff,")); 
        printer.println(F("n'importe quoi.")); 
      }
  
      choice = (choice + 1) % 5;
      printer.feed(8);
    }
    else {
      printer.feed(nbLines);
    }
    
    printer.sleep();   
  }
}
