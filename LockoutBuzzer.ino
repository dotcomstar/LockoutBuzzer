const int kRedBuzzers[][2] = {{13, 7}};  // LED, button
const int kGreenBuzzers[][2] = {{12, 6}};  // LED, button
const int kLockout_LED = 11;
const int kBuzzerSpeaker = 8;
const int kResetButton = 5;
bool is_locked_out = false;

void TestLEDs();
void PlayTone(int frequency = 1000, int duration = 1000);
void TestButtons();
bool is_pressed(const int button_port);
bool is_reset_pressed();

void setup() {
  Serial.begin(9600);
  Serial.println(F("Started setup()\n"));
  for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
    int current_LED = kRedBuzzers[current_buzzer][0];
    int current_button = kRedBuzzers[current_buzzer][1];
    pinMode(current_LED, OUTPUT);
    pinMode(current_button, INPUT);
  }
  for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
    int current_LED = kGreenBuzzers[current_buzzer][0];
    int current_button = kGreenBuzzers[current_buzzer][1];
    pinMode(current_LED, OUTPUT);
    pinMode(current_button, INPUT);
  }
  pinMode(kLockout_LED, OUTPUT);
  pinMode(kBuzzerSpeaker, OUTPUT);
  pinMode(kResetButton, INPUT);
}

void loop() {
  if (is_locked_out) {
    digitalWrite(kLockout_LED, HIGH);
    if (is_reset_pressed()) {
      is_locked_out = false;
      TurnOff_LEDs();
      delay(10);  // Gets around weird collisions.
      noTone(kBuzzerSpeaker);
    }
  } else {  // Not locked out.
    digitalWrite(kLockout_LED, LOW);
    for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
      int current_LED = kRedBuzzers[current_buzzer][0];
      int current_button = kRedBuzzers[current_buzzer][1];
      if(is_locked_out) {
        break;
      }
      if (is_pressed(current_button)) {
        is_locked_out = true;
        digitalWrite(current_LED, HIGH);
        PlayTone(1000);
        break;
      }
    }
    for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
      int current_LED = kGreenBuzzers[current_buzzer][0];
      int current_button = kGreenBuzzers[current_buzzer][1];
      if(is_locked_out) {
        break;
      }
      if (is_pressed(current_button)) {
        is_locked_out = true;
        digitalWrite(current_LED, HIGH);
        PlayTone(1005);
        break;
      }
    }
  }
}

void TurnOff_LEDs() {
  digitalWrite(kLockout_LED, LOW);
  for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
    int current_LED = kRedBuzzers[current_buzzer][0];
    digitalWrite(current_LED, LOW);
  }
  for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
    int current_LED = kGreenBuzzers[current_buzzer][0];
    digitalWrite(current_LED, LOW);
  }
}

bool is_pressed(const int button_port) {
  return digitalRead(button_port) == 1;
}

bool is_reset_pressed() {
  return is_pressed(kResetButton);
}

void PlayTone(int frequency /*= 1000*/, int duration /*= 1000*/) {
  Serial.print(F("Playing tone at ")); Serial.print(frequency); Serial.print(F(" Hz for ")); Serial.print(duration); Serial.println(F(" ms"));
  tone(kBuzzerSpeaker, frequency, duration);
  Serial.println("Finished playing tone");
}

void Test_LEDs() {
  Serial.println("Started TestLEDs()");
  for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
    int current_LED = kRedBuzzers[current_buzzer][0];
    digitalWrite(current_LED, HIGH);
  }
  for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
    int current_LED = kGreenBuzzers[current_buzzer][0];
    digitalWrite(current_LED, HIGH);
  }
  digitalWrite(kLockout_LED, HIGH);
  delay(1000);
  for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
    int current_LED = kRedBuzzers[current_buzzer][0];
    digitalWrite(current_LED, LOW);
  }
  for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
    int current_LED = kGreenBuzzers[current_buzzer][0];
    digitalWrite(current_LED, LOW);
  }
  digitalWrite(kLockout_LED, LOW);
  delay(1000);
  Serial.println("Finished TestLEDs()");
}

void TestButtons() {
  int number_of_buttons_counted = 0;
  for (int current_buzzer = 0; current_buzzer < sizeof(kRedBuzzers)/sizeof(kRedBuzzers[0]); current_buzzer++) {
    int current_button = kRedBuzzers[current_buzzer][1];
    Serial.print(F("Button ")); Serial.print(number_of_buttons_counted); Serial.print(F(" (red): ")); Serial.print(digitalRead(current_button)); Serial.print(F(", "));
    number_of_buttons_counted++;
  }
  for (int current_buzzer = 0; current_buzzer < sizeof(kGreenBuzzers)/sizeof(kGreenBuzzers[0]); current_buzzer++) {
    int current_button = kGreenBuzzers[current_buzzer][1];
    Serial.print(F("Button ")); Serial.print(number_of_buttons_counted); Serial.print(F(" (green): ")); Serial.print(digitalRead(current_button)); Serial.print(F(", "));
    number_of_buttons_counted++;
  }
  Serial.print("Reset Button: "); Serial.println(digitalRead(kResetButton));
}
