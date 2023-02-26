// fast synchronous output on pins 2 and 3
inline void output(int value) {
  // 2 is PD2, 3 is PD3
  if (value) {
    PORTD = PORTD | 0b00001100;
  }
  else {
    PORTD = PORTD & 0b11110011;
  }
}

void setup() {
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // oscillators (on different PWM channels)
  analogWrite(5, analogRead(A2));
  analogWrite(6, analogRead(A2));
  
  // sampling channels
  float i0 = analogRead(A0) / 1023.0;
  float i1 = analogRead(A1) / 1023.0;

  // output gain channels
  float g0 = analogRead(A4) / 1023.0;
  float g1 = analogRead(A5) / 1023.0;

  // output gain
  float gain = (analogRead(A3) / 1023.0) + 1;

  // write output
  float val = (i0 * g0 + i1 * g1) * gain;
  output(val > 0.5);
  Serial.println(i0);
}
