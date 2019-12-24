#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_G5 784

#define BUTTON 2
#define BUZZER 8


/* ----- Variables ----- */
enum Mode {
  Bounce,
  Split,
  Charge,
  Loading,
  Random
};

volatile Mode mode;
volatile Mode prev;
volatile unsigned long buttonTimer = 0;


/* ----- Setup function ----- */
void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  for (int pin = 3; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
  }
  startFX();
  mode = Mode::Bounce;
  prev = mode;
  attachInterrupt(digitalPinToInterrupt(BUTTON), changeMode, FALLING);
}


/* ----- Loop function ----- */
void loop() {
  if (mode == Mode::Bounce) {
    modeBounce();
  }
  else if (mode == Mode::Split) {
    modeSplit();
  }
  else if (mode == Mode::Charge) {
    modeCharge();
  }
  else if (mode == Mode::Loading) {
    modeLoading();
  }
  else if (mode == Mode::Random) {
    modeRandom();
  }

  if (mode != prev) {
    changeFX();
    prev = mode;
  }
}


/* ----- ALL Functions ----- */
void startFX() {
  int melody[] = {
    NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5
  };
  int noteDurations[] = {
    10, 10, 10, 10
  };
  for (int i = 0; i < 4; i++) {
    int duration = 1000 / noteDurations[i];
    tone(BUZZER, melody[i], duration);
    int pause = duration * 1.30;
    delay(pause);
    noTone(BUZZER);
  }
}

void changeFX() {
  for (int pin = 3; pin < 14; pin++) {
    digitalWrite(pin, LOW);
  }
  tone(BUZZER, NOTE_C5, 100);
  delay(100);
  tone(BUZZER, NOTE_G5, 100);
  delay(100);
  noTone(BUZZER);
}

void changeMode() {
  if ((unsigned long)(millis() - buttonTimer) > 500) {
    mode = Mode((mode + 1) % 5);
    buttonTimer = millis();
  }
}

void modeBounce() {
  for (int pin = 3; pin <= 13 and mode == Mode::Bounce; pin++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }
  for (int pin = 13; pin >= 3 and mode == Mode::Bounce; pin--) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }
}

void modeSplit() {
  for (int pin = 3; pin <= 7 and mode == Mode::Split; pin++) {
    digitalWrite(pin, HIGH);
    digitalWrite(16 - pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    digitalWrite(16 - pin, LOW);
  }
  for (int pin = 7; pin >= 3 and mode == Mode::Split; pin--) {
    digitalWrite(pin, HIGH);
    digitalWrite(16 - pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    digitalWrite(16 - pin, LOW);
  }
}

void modeCharge() {
  for (int pin = 3; pin <= 13 and mode == Mode::Charge; pin++) {
    digitalWrite(pin, HIGH);
    delay(100);
  }
  for (int pin = 13; pin >= 3 and mode == Mode::Charge; pin--) {
    digitalWrite(pin, LOW);
    delay(100);
  }
}

void modeLoading() {
  for (int pin = 0; pin <= 10 and mode == Mode::Loading; pin++) {
    int p1 = pin + 3;
    int p2 = ((pin + 1) % 11) + 3;
    int p3 = ((pin + 2) % 11) + 3;
    digitalWrite(p1, HIGH);
    digitalWrite(p2, HIGH);
    digitalWrite(p3, HIGH);
    delay(100);
    digitalWrite(p1, LOW);
  }
}

void modeRandom() {
  int randPin[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  for (int i = 0; i < 11; i++) {
    int j = rand() % i;
    int tmp = randPin[i];
    randPin[i] = randPin[j];
    randPin[j] = tmp;
  }
  for (int i = 0; i <= 10 and mode == Mode::Random; i++) {
    digitalWrite(randPin[i], HIGH);
    delay(150);
  }
  for (int i = 10; i >= 0 and mode == Mode::Random; i--) {
    digitalWrite(randPin[i], LOW);
    delay(150);
  }
}
