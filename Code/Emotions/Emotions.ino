
int speakerPin = 2;
#include <Emotions.h>
Emotions Emote(speakerPin);


void setup() {
  Serial.begin(115200);
  
  randomSeed(analogRead(0)); // randomness
}


void loop() {
  int mood = random(10);

  switch (mood) {
    case 0:
      Serial.printf("Happy\n");
      Emote.happySound();

      break;
    case 1:
      Serial.printf("curiousSound\n");
      Emote.curiousSound();
      break;
    case 2:
      Serial.printf("sadSound\n");
      Emote.sadSound();
      break;
    case 3:
      Serial.printf("alertSound\n");
      Emote.alertSound();
      break;
    case 4:
      Serial.printf("idleSound\n");
      Emote.idleSound();
      break;
    case 5: Emote.backChat(); break;
    case 6: Emote.muttering(); break;
    case 7: Emote.nervous(); break;
    case 8: Emote.scared(); break;
    case 9: delay(100); break;
  }

  Emote.Quiet();
  delay(random(300, 1500)); // natural pauses
}