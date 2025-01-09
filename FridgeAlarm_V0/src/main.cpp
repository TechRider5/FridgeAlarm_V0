void selectRandomSong() {
  // Use both time and analog noise for better randomization
  long randNumber = analogRead(0) + millis();
  int song_choice = randNumber % 5; // Get remainder of division by 5 (0-4)
  
  switch(song_choice) {
    case 0:
      current_melody = mario_melody;
      current_durations = mario_durations;
      current_song_length = sizeof(mario_melody) / sizeof(mario_melody[0]);
      break;
    case 1:
      current_melody = jingle_melody;
      current_durations = jingle_durations;
      current_song_length = sizeof(jingle_melody) / sizeof(jingle_melody[0]);
      break;
    case 2:
      current_melody = imperial_melody;
      current_durations = imperial_durations;
      current_song_length = sizeof(imperial_melody) / sizeof(imperial_melody[0]);
      break;
    case 3:
      current_melody = twinkle_melody;
      current_durations = twinkle_durations;
      current_song_length = sizeof(twinkle_melody) / sizeof(twinkle_melody[0]);
      break;
    case 4:
      current_melody = birthday_melody;
      current_durations = birthday_durations;
      current_song_length = sizeof(birthday_melody) / sizeof(birthday_melody[0]);
      break;
  }
}

void setup() {
  pinMode(PiezoPin, OUTPUT);
  delay(15000);  // Initial delay
  // Multiple random seeds for better randomization
  randomSeed(analogRead(0) + millis());
  for(int i = 0; i < 10; i++) {  // Mix up the random number generator
    random(100);
    delay(1);
  }
  selectRandomSong();
} 