/*
 * Hand Gesture Controlled Car — RECEIVER
 * Author: Anubhav Srivastava
 *
 * Hardware: Arduino UNO + 433 MHz RF RX + HT12D Decoder + L293D Motor Driver
 *
 * Pin Mapping (HT12D D0–D3 outputs → Arduino analog pins used as digital inputs):
 *   A0 → Forward  signal
 *   A1 → Backward signal
 *   A2 → Right    signal
 *   A3 → Left     signal
 *
 * Motor wiring (via AFMotor shield):
 *   Motor channel 3 → Right motor
 *   Motor channel 4 → Left  motor
 *
 * FIX summary vs. original:
 *   - pinMode declarations corrected to match actual input pins (A0–A3)
 *   - digitalRead corrected to match declared pins (was reading A0/A1 undeclared)
 *   - Added motor stop when direction signals are absent (was missing STOP state)
 *   - Added Serial debug output for all states
 */

#include <AFMotor.h>

// ── Motor objects ─────────────────────────────────────────────────────────────
AF_DCMotor motorRight(3);   // Right-side motor on channel 3
AF_DCMotor motorLeft(4);    // Left-side motor  on channel 4

// ── Input pins (HT12D data outputs) ──────────────────────────────────────────
const int PIN_FWD   = A0;
const int PIN_BWD   = A1;
const int PIN_RIGHT = A2;
const int PIN_LEFT  = A3;

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  // FIX: original declared A2–A5 but read from A0/A1; now consistent
  pinMode(PIN_FWD,   INPUT);
  pinMode(PIN_BWD,   INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_LEFT,  INPUT);

  Serial.begin(9600);
  Serial.println("Receiver ready.");

  motorRight.setSpeed(255);
  motorLeft.setSpeed(255);

  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
}

// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  bool fwd   = digitalRead(PIN_FWD)   == HIGH;
  bool bwd   = digitalRead(PIN_BWD)   == HIGH;
  bool right = digitalRead(PIN_RIGHT) == HIGH;
  bool left  = digitalRead(PIN_LEFT)  == HIGH;

  if (fwd) {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    Serial.println("Forward");
  }
  else if (bwd) {
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
    Serial.println("Backward");
  }
  else if (right) {
    // Right turn: right motor stops, left motor drives
    motorRight.run(RELEASE);
    motorLeft.run(FORWARD);
    Serial.println("Right");
  }
  else if (left) {
    // Left turn: left motor stops, right motor drives
    motorRight.run(FORWARD);
    motorLeft.run(RELEASE);
    Serial.println("Left");
  }
  else {
    // FIX: explicit STOP state — original had this inside an if(all LOW) block
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);
    Serial.println("Stop");
  }

  delay(100);
}
