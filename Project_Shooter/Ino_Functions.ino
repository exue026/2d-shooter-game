double getTime() {
  return double(millis());
}

void LightRLED() {
  digitalWrite(RLED, 1);
  digitalWrite(GLED, 0);
}

void LightGLED() {
  digitalWrite(GLED, 1);
  digitalWrite(RLED, 0);
}
