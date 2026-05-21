/*
 * Hand Gesture Controlled Car — TRANSMITTER
 * Author: Anubhav Srivastava
 *
 * Hardware: Arduino UNO + ADXL335 Accelerometer + HT12E Encoder + 433 MHz RF TX
 *
 * Pin Mapping:
 *   A0 → ADXL335 X-axis output
 *   A1 → ADXL335 Y-axis output  (was incorrectly set as OUTPUT in original)
 *   D9  → HT12E D0 (Forward)
 *   D10 → HT12E D1 (Backward)
 *   D11 → HT12E D2 (Right)
 *   D12 → HT12E D3 (Left)
 *
 * Thresholds (ADC 0–1023 at 5V, neutral ≈ 512 / ~2.5 V):
 *   Forward  : Y-axis >= 590  (~2.9 V, tilt forward)
 *   Backward : Y-axis <= 430  (~2.1 V, tilt backward)
 *   Right    : X-axis >= 590
 *   Left     : X-axis <= 430
 *   Dead-zone: both axes 430 < val < 590 → STOP
 */

// ── Pin definitions ──────────────────────────────────────────────────────────
const int PIN_X       = A0;
const int PIN_Y       = A1;   // FIX: was A3 & set as OUTPUT in original

const int PIN_FWD     = 9;
const int PIN_BWD     = 10;
const int PIN_RIGHT   = 11;
const int PIN_LEFT    = 12;

// ── Threshold values ─────────────────────────────────────────────────────────
const int THRESH_HIGH = 590;  // FIX: original used 380/390 — too close to neutral
const int THRESH_LOW  = 430;  // FIX: original used 310/320 — asymmetric dead-zone

// ── State tracking ───────────────────────────────────────────────────────────
enum Direction { NONE, FORWARD, BACKWARD, RIGHT_DIR, LEFT_DIR };
Direction lastDirection = NONE;

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  pinMode(PIN_X,     INPUT);
  pinMode(PIN_Y,     INPUT);
  pinMode(PIN_FWD,   OUTPUT);
  pinMode(PIN_BWD,   OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_LEFT,  OUTPUT);

  // Start all outputs LOW (motors stopped)
  stopAll();

  Serial.begin(9600);
  Serial.println("Transmitter ready.");
}

// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  int x = analogRead(PIN_X);
  int y = analogRead(PIN_Y);

  Serial.print("X="); Serial.print(x);
  Serial.print("  Y="); Serial.println(y);

  Direction dir = NONE;

  // Priority: Y-axis (forward/backward) checked first
  if      (y >= THRESH_HIGH) dir = FORWARD;
  else if (y <= THRESH_LOW)  dir = BACKWARD;
  else if (x >= THRESH_HIGH) dir = RIGHT_DIR;
  else if (x <= THRESH_LOW)  dir = LEFT_DIR;

  // Only update outputs when direction changes (reduces RF chatter)
  if (dir != lastDirection) {
    stopAll();
    switch (dir) {
      case FORWARD:   digitalWrite(PIN_FWD,   HIGH); Serial.println(">> FORWARD");  break;
      case BACKWARD:  digitalWrite(PIN_BWD,   HIGH); Serial.println(">> BACKWARD"); break;
      case RIGHT_DIR: digitalWrite(PIN_RIGHT, HIGH); Serial.println(">> RIGHT");    break;
      case LEFT_DIR:  digitalWrite(PIN_LEFT,  HIGH); Serial.println(">> LEFT");     break;
      default:                                        Serial.println(">> STOP");     break;
    }
    lastDirection = dir;
  }

  delay(100);  // FIX: reduced from 200 ms for snappier response
}

// ─────────────────────────────────────────────────────────────────────────────
void stopAll() {
  digitalWrite(PIN_FWD,   LOW);
  digitalWrite(PIN_BWD,   LOW);
  digitalWrite(PIN_RIGHT, LOW);
  digitalWrite(PIN_LEFT,  LOW);
}
