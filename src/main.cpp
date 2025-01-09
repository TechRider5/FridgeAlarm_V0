#include <Arduino.h>

// Define note frequencies
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

const int PiezoPin = 17;

// Happy Birthday melody
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_B4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

// Note durations (in ms)
int noteDurations[] = {
  200, 200, 400, 400, 400, 800,
  200, 200, 400, 400, 400, 800,
  200, 200, 400, 400, 400, 400, 400,
  200, 200, 400, 400, 400, 800
};

void setup() {
  pinMode(PiezoPin, OUTPUT);
  delay(10000);  
}

void loop() {

  // Play the melody
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    tone(PiezoPin, melody[i]);
    delay(noteDurations[i]);
    noTone(PiezoPin);
    delay(50); // Short pause between notes
  }
  
  delay(2000); // Wait 2 seconds before playing again
}
