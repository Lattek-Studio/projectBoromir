#define ENA D3
#define IN1 D4
#define IN2 D5

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,255);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

}
