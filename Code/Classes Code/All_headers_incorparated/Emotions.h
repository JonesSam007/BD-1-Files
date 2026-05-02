
class Emotions{
public:
int speaker;
public: 

  Emotions(int _speakerPin){
    speaker = _speakerPin;
    ledcAttach(speaker, 2000, 10);
  }

  void playTone(int freq, int duration) {
    ledcWriteTone(speaker, freq);
    delay(duration);
  }

  void silence(int t = 50) {
    ledcWriteTone(speaker, 0);
    delay(t);
  }

  // Helpers
  int jitter(int base, int variation) {
    return base + random(-variation, variation);
  }

  // Core sound shapes
  void chirpUp(int startF, int endF, int stepDelay) {
    for (int f = startF; f < endF; f += random(15, 30)) {
      ledcWriteTone(speaker, jitter(f, 20));
      delay(stepDelay + random(-2, 3));
    }
  }

  void chirpDown(int startF, int endF, int stepDelay) {
    for (int f = startF; f > endF; f -= random(15, 30)) {
      ledcWriteTone(speaker, jitter(f, 20));
      delay(stepDelay + random(-2, 3));
    }
  }

  // =======================
  //        EMOTIONS
  // =======================

  // Happy
  void happySound() {
    chirpUp(500, 1400, 4);
    silence(30);
    chirpUp(700, 1600, 3);
  }

  // Curious
  void curiousSound() {
    playTone(jitter(600, 50), 80);
    silence(20);
    playTone(jitter(900, 80), 60);
    silence(20);
    playTone(jitter(500, 50), 120);
  }

  // Sad
  void sadSound() {
    chirpDown(900, 300, 8);
    silence(50);
    playTone(350, 200);

  }

  // Alert
  void alertSound() {
    for (int i = 0; i < 3; i++) {
      playTone(jitter(1200, 100), 80);
      silence(40);
    }
  }

  void idleSound() {
    int choice = random(8);

    switch (choice) {

      // Soft upward chirp (curious idle)
      case 0:
        chirpUp(400, 900, 6);
        break;

      // Soft downward chirp (relaxed)
      case 1:
        chirpDown(1000, 500, 7);
        break;

      // Single questioning beep
      case 2:
        playTone(jitter(700, 100), 120);
        silence(40);
        playTone(jitter(900, 120), 80);
        break;

      // Tiny double chirp
      case 3:
        playTone(jitter(800, 80), 60);
        silence(20);
        playTone(jitter(1000, 80), 60);
        break;

      // Quiet mutter fragment
      case 4:
        for (int i = 0; i < random(2, 4); i++) {
          playTone(jitter(350, 60), random(50, 100));
          silence(random(20, 40));
        }
        break;

      // Fast little blips (processing/thinking)
      case 5:
        for (int i = 0; i < random(3, 6); i++) {
          playTone(jitter(1100, 150), 30);
          silence(15);
        }
        break;

      // Rising “hmm?” sound
      case 6:
        chirpUp(500, 1000, 5);
        silence(30);
        playTone(jitter(600, 50), 100);
        break;

      // Glitchy/random noise (very BD-1 style)
      case 7:
        for (int i = 0; i < random(4, 8); i++) {
          ledcWriteTone(speaker, random(300, 1400));
          delay(random(20, 60));
        }
        break;
    }

    // occasional micro pause (very important for realism)
    silence(random(50, 150));
  }


  // Back-chatting (argumentative, rapid response beeps)
  void backChat() {
    for (int i = 0; i < random(3, 6); i++) {
      playTone(jitter(800, 200), random(40, 90));
      silence(random(10, 40));
      playTone(jitter(1200, 200), random(40, 80));
      silence(random(20, 60));
    }
  }

  // Muttering (low, grumbly, under-the-breath sounds)
  void muttering() {
    for (int i = 0; i < random(4, 8); i++) {
      playTone(jitter(300, 80), random(60, 120));
      silence(random(20, 50));
    }
    chirpDown(600, 250, 10); // trailing grumble
  }

  // Scared (sudden high pitch + drop)
  void scared() {
    playTone(1500 + random(0, 300), 100);
    silence(30);
    chirpDown(1400, 400, 4);
    silence(50);
    playTone(jitter(500, 100), 120);
  }

  // Nervous (stuttering + uneven tones)
  void nervous() {
    for (int i = 0; i < random(5, 10); i++) {
      playTone(jitter(700, 150), random(30, 70));
      silence(random(10, 30));
    }
    chirpUp(600, 1000, 6);
  }

  // R2-D2 style wailing scream
  void wailingScream() {
    // long rising sweep
    for (int f = 400; f < 2000; f += 15) {
      ledcWriteTone(speaker, jitter(f, 30));
      delay(3);
    }

    // oscillating high-pitch wail
    for (int i = 0; i < 20; i++) {
      ledcWriteTone(speaker, 1800 + random(-200, 200));
      delay(30);
    }

    // falling panic drop
    for (int f = 2000; f > 300; f -= 20) {
      ledcWriteTone(speaker, jitter(f, 40));
      delay(4);
    }

    silence(100);
  }

  void Quiet(){silence(1);}
};
