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

bool set = false;
bool swap;
unsigned long timer;
int pin, pin2;
int flag, flag2;


/* Set up here */
void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(BUTTON, INPUT_PULLUP);
  for (int pin = 3; pin < 14; pin++) {
    pinMode(pin, OUTPUT);
  }
  startFX();
}


/* ----- Loop here ----- */
void loop() {
  if (digitalRead(BUTTON) == LOW) {
    mode = (mode == MODE::RANDOM) ? MODE::BOUNCE : MODE(mode + 1);
    set = false;
    changeFX();
    delay(100);
  }
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

void changeFX() {
  tone(BUZZER, NOTE_C5, 100);
  delay(100);
  tone(BUZZER, NOTE_G5, 100);
  delay(100);
  noTone(BUZZER);
}

void modeBounce() {
  if (!set) {
    set = true;
    timer = 0;
    pin = 3;
    flag = 13;
  }

  Serial.println(pin);
  if (millis() - timer > 100) {
    digitalWrite(pin, LOW);
    pin = (swap) ? pin - 1 : pin + 1;
    if (pin > 12) {
      swap = true;
    }
    else if (pin < 4) {
      swap = false;
    }
    timer = millis();
    digitalWrite(pin, HIGH);
  }


}

void modeHalf() {

}

void modeCharge() {

}

void modeLoading() {

}

void modeRandom() {

}
