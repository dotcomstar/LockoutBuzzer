const int kRed_LED = 13;
const int kGreen_LED = 12;
const int kLockout_LED = 11;
const int kBuzzer = 8;
const int kTopButton = 7;
const int kBottomButton = 6;
const int kResetButton = 5;
bool is_locked_out = false;

void TestLEDs();
void PlayTone(int frequency = 1000, int duration = 1000);
void TestButtons();
bool is_top_pressed();
bool is_bottom_pressed();
bool is_reset_pressed();

void setup() {
  Serial.begin(9600);
  Serial.println(F("Started setup()\n"));
  pinMode(kRed_LED, OUTPUT);
  pinMode(kGreen_LED, OUTPUT);
  pinMode(kLockout_LED, OUTPUT);
  pinMode(kBuzzer, OUTPUT);
  pinMode(kTopButton, INPUT);
  pinMode(kBottomButton, INPUT);
  pinMode(kResetButton, INPUT);
  Serial.println(F("\nFinished setup()"));
}

void loop() {
  if (is_locked_out) {
    digitalWrite(kLockout_LED, HIGH);
    if (is_reset_pressed()) {
      is_locked_out = false;
      digitalWrite(kRed_LED, LOW);
      digitalWrite(kGreen_LED, LOW);
      digitalWrite(kLockout_LED, LOW);
      delay(10);  // Gets around weird collisions.
      noTone(kBuzzer);
    }
  } else {  // Not locked out
    digitalWrite(kLockout_LED, LOW);
    if (is_top_pressed()) {
      is_locked_out = true;
      digitalWrite(kRed_LED, HIGH);
      PlayTone(1000);
    } else if (is_bottom_pressed()) {
      is_locked_out = true;
      digitalWrite(kGreen_LED, HIGH);
      PlayTone(1005);
    }
  }
}

void TestLEDs() {
  Serial.println("Started TestLEDs()");
  digitalWrite(kRed_LED, HIGH);
  digitalWrite(kGreen_LED, HIGH);
  digitalWrite(kLockout_LED, HIGH);
  delay(1000);
  digitalWrite(kRed_LED, LOW);
  digitalWrite(kGreen_LED, LOW);
  digitalWrite(kLockout_LED, LOW);
  Serial.println("Finished TestLEDs()");
}

void PlayTone(int frequency /*= 1000*/, int duration /*= 1000*/) {
  Serial.print(F("Playing tone at ")); Serial.print(frequency); Serial.print(F(" Hz for ")); Serial.print(duration); Serial.println(F(" ms"));
  tone(kBuzzer, frequency, duration);
  Serial.println("Finished playing tone");
}

void TestButtons() {
  Serial.print("Top button: "); Serial.print(digitalRead(kTopButton)); Serial.print(", Bottom button: "); Serial.print(digitalRead(kBottomButton));
  Serial.print(", Reset Button: "); Serial.println(kResetButton);
}

bool is_top_pressed() {
  return digitalRead(kTopButton) == 1;
}

bool is_bottom_pressed() {
  return digitalRead(kBottomButton) == 1;
}

bool is_reset_pressed() {
  return digitalRead(kResetButton) == 1;
}
