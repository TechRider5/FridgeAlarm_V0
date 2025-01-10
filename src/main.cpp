#include <Arduino.h>

// Define note frequencies
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST     0

const int PiezoPin = 17;
unsigned long lastSongChange = 0;
int currentSongIndex = 0;

// Brahms' Lullaby
int lullaby_melody[] = {
  NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_C4,
  NOTE_G4, NOTE_G4, NOTE_AS4, NOTE_G4, NOTE_DS4,
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_DS5, NOTE_C5, NOTE_AS4, NOTE_F4, NOTE_DS4,
  NOTE_C4
};

int lullaby_durations[] = {
  400, 400, 400, 400, 400, 800,
  400, 400, 400, 400, 800,
  400, 400, 400, 400, 400, 400, 400, 400,
  800
};

// Greensleeves
int greensleeves_melody[] = {
  NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_D5,
  NOTE_DS5, NOTE_D5, NOTE_C5, NOTE_A4,
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_G4, NOTE_F4, NOTE_G4
};

int greensleeves_durations[] = {
  400, 400, 200, 600,
  200, 200, 200, 600,
  200, 200, 200, 600,
  200, 200, 800
};

// Pachelbel's Canon in D
int canon_melody[] = {
  NOTE_D4, NOTE_A4, NOTE_B4, NOTE_FS4,
  NOTE_G4, NOTE_D4, NOTE_G4, NOTE_A4,
  NOTE_D4, NOTE_A4, NOTE_B4, NOTE_FS4,
  NOTE_G4, NOTE_D4, NOTE_G4, NOTE_A4
};

int canon_durations[] = {
  500, 500, 500, 500,
  500, 500, 500, 500,
  500, 500, 500, 500,
  500, 500, 500, 500
};

// Variables to store the selected song
int* current_melody;
int* current_durations;
int current_song_length;

void playSong() {
  for (int i = 0; i < current_song_length; i++) {
    if (current_melody[i] == 0) {
      delay(current_durations[i]);
    } else {
      tone(PiezoPin, current_melody[i]);
      delay(current_durations[i]);
      noTone(PiezoPin);
    }
    delay(100); // Longer pause between notes for calmer feel
  }
}

void selectRandomSong() {
  // Get random noise from unconnected analog pin
  int noise1 = analogRead(0);
  delay(100);
  int noise2 = analogRead(0);
  delay(100);
  int noise3 = analogRead(0);
  
  // Use the noise to select a random song (0-2)
  currentSongIndex = ((noise1 + noise2 + noise3) & 0x7) % 3;
  
  switch(currentSongIndex) {
    case 0:
      current_melody = lullaby_melody;
      current_durations = lullaby_durations;
      current_song_length = sizeof(lullaby_melody) / sizeof(lullaby_melody[0]);
      break;
    case 1:
      current_melody = greensleeves_melody;
      current_durations = greensleeves_durations;
      current_song_length = sizeof(greensleeves_melody) / sizeof(greensleeves_melody[0]);
      break;
    case 2:
      current_melody = canon_melody;
      current_durations = canon_durations;
      current_song_length = sizeof(canon_melody) / sizeof(canon_melody[0]);
      break;
  }
}

void setup() {
  pinMode(PiezoPin, OUTPUT);
  delay(15000);  // Initial delay
  selectRandomSong(); // Choose first random song
  lastSongChange = millis();
}

void loop() {
  // Change to a new random song every 10 seconds (longer for calmer transitions)
  if (millis() - lastSongChange >= 10000) {
    selectRandomSong();
    lastSongChange = millis();
  }
  
  playSong();
  delay(5000); // Wait 5 seconds before playing again
} 