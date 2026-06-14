const int PIR_PIN     = 2;
const int RELAY_PIN   = 7;
const int SPRAY_MS    = 150;
const int COOLDOWN_MS = 8000;

bool onCooldown = false;
unsigned long cooldownStart = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // active-LOW: HIGH = OFF

  Serial.begin(9600);
  Serial.println("Waiting for PIR to settle...");

  // Wait until PIR reads LOW for 10 uninterrupted seconds
  unsigned long lowSince = 0;
  while (true) {
    if (digitalRead(PIR_PIN) == LOW) {
      if (lowSince == 0) lowSince = millis();
      if (millis() - lowSince >= 10000) break; // stable for 10s = ready
    } else {
      lowSince = 0; // PIR spiked HIGH -- reset and wait again
      Serial.println("PIR still warming up...");
    }
  }

  Serial.println("Cat Sprayer Ready.");
}

void loop() {
  if (onCooldown &&
      (millis() - cooldownStart >= COOLDOWN_MS)) {
    onCooldown = false;
    Serial.println("Cooldown done. Ready.");
  }
  if (!onCooldown && digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Motion detected! Spraying...");
    spray();
  }
}

void spray() {
  digitalWrite(RELAY_PIN, LOW);   // pump ON
  delay(SPRAY_MS);
  digitalWrite(RELAY_PIN, HIGH);  // pump OFF
  Serial.println("Spray done. Cooling down...");
  onCooldown = true;
  cooldownStart = millis();
}
