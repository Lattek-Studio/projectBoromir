

#include <Servo.h>

//DC Pins
#define ENA D3
#define IN1 D4
#define IN2 D5
//Servo pin
#define PWM_SERVO D6

Servo myservo;

void setup() {
  //Setup DC
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,0);

  //Setup Servo
  myservo.attach(PWM_SERVO);
  myservo.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
