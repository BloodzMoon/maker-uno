#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5 784

#define BUTTON 2
#define BUZZER 8

/* ----- Global variables ----- */
enum MODE {
  BOUNCE,
  HALF,
  CHARGE,
  LOADING,
  RANDOM
};
MODE mode = MODE::BOUNCE;

int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5
};

int noteDurations[] = {
  10, 10, 10, 10
};

unsigned long buttonTimer;
bool pressed = false;
bool set = false;
bool swap;
unsigned long timer;
int pin, pin2;
int flag, flag2;


/* Set up here */
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(BUTTON, INPUT_PULLUP);
  for (int pin = 3; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(BUTTON), changeMode, FALLING);
  startFX();
}


/* ----- Loop here ----- */
void loop() {
  Serial.println(mode);
  switch (mode) {
    case MODE::BOUNCE :
      modeBounce();
      break;
    case MODE::HALF :
      modeHalf();
      break;
    case MODE::CHARGE :
      modeCharge();
      break;
    case MODE::LOADING :
      modeLoading();
      break;
    case MODE::RANDOM :
      modeRandom();
      break;
  }
}


/* ----- Functions here ----- */
void startFX() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
}


void changeMode() {
  set = false;
  for (int pin = 3; pin < 14; pin++) {
    digitalWrite(pin, LOW);
  }
  tone(BUZZER, NOTE_C5, 100);
  delay(100);
  tone(BUZZER, NOTE_G5, 100);
  delay(100);
  noTone(BUZZER);
  mode = MODE((mode + 1) % 5);
}

void modeBounce() {
  for (int pin = 3; pin <= 13; pin++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }
  for (int pin = 13; pin >= 3; pin--) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
  }
}

void modeHalf() {
  for (int pin = 3; pin <= 7; pin++) {
    digitalWrite(pin, HIGH);
    digitalWrite(16 - pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    digitalWrite(16 - pin, LOW);
  }
  for (int pin = 7; pin >= 3; pin--) {
    digitalWrite(pin, HIGH);
    digitalWrite(16 - pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    digitalWrite(16 - pin, LOW);
  }
}

void modeCharge() {
  for (int pin = 3; pin <= 13; pin++) {
    digitalWrite(pin, HIGH);
    delay(100);
  }
  for (int pin = 13; pin >= 3; pin--) {
    digitalWrite(pin, LOW);
    delay(100);
  }
}

void modeLoading() {
  for (int pin = 0; pin <= 10; pin++) {
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
  int arr[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  for (int i = 0; i < 11; i++) {
    int j = rand() % i;
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
  for (int i = 0; i < 11; i++) {
    digitalWrite(arr[i], HIGH);
    delay(150);
  }
  for (int i = 10; i >= 0; i--) {
    digitalWrite(arr[i], LOW);
    delay(150);
  }
}
