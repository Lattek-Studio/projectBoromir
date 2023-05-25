

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

void fan_on()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,255);
}
void fan_off()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,0);
}

void loop() {
  fan_on();
  delay(1000);
  fan_off();
  delay(1000);

}
