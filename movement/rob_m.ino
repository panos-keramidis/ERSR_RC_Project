#include <ShiftySoftServo.h>
#include <Shifty.h>
#include <Arduino.h>

//Motor A
#define motorPin1 1
#define motorPin2 2
#define enable1 3
//Motor B
#define motorPin3 4
#define motorPin4 5
#define enable2 6

#define pingPin 10 // Trigger Pin of Ultrasonic Sensor
#define echoPin 11 // Echo Pin of Ultrasonic Sensor

Shifty shift;

void setup()
{

  shift.setBitCount(8);
  shift.setPins(8, 13, 12);

  // Set all the motor control pins to outputs
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Set Ultrasonic Sensor pins
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Turn off motors - Initial state
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  Serial.begin(9600);
}

void loop()
{

  arm.setDegreesOfRotation(90);
  arm.update(shift);
  Serial.println("hi2");
  

  // long cm = see();
  // if (cm < 7)
  // {
  //   stopm();
  //   if (!use_arm())
  //   {
  //     speed_control(0);
  //     move_backward();
  //     delay(1000);
  //     turn_left();
  //     Serial.println("turning");
  //     // while (cm < 26)
  //     // {
  //     //   cm = see();
  //     //   delay(100);
  //     // }
  //   }
  // }
  // else
  // {
  //   move_forward();
  //   if (cm < 50)
  //     speed_control(0);
  //   else if (cm < 106)
  //     speed_control((cm - 56) * 2);
  //   else
  //     speed_control(100);
  // }
  // delay(100);


}

void stopm()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void move_forward()
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void move_backward()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void turn_left()
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void turn_right()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void speed_control(int speed)
{
  speed_control_left(speed);
  speed_control_right(speed);
}

void speed_control_right(int speed)
{
  analogWrite(enable1, 195 + speed * 0.6);
}

void speed_control_left(int speed)
{
  analogWrite(enable2, 185 + speed * 0.7);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

bool use_arm()
{
  // Serial.println("hi");
  // arm.moveToDegrees(0);
  //   Serial.println("hi2");

  // arm.update();
  // base.moveToDegrees(0);
  // base.update();
  //   Serial.println("hi3");

  return false;
}

long see()
{
  long duration, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}