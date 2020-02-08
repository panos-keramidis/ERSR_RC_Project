#include <Servo.h>
#include <Shifty.h>
#include <Arduino.h>

// Motor A
#define motorPin1 4 // 4 on shift register
#define motorPin2 3 // 3 on shift register
#define enable1 9   // 9 pin on arduino
// Motor B
#define motorPin3 2 // 2 on shift register
#define motorPin4 1 // 1 on shift register
#define enable2 10  // 10 pin on arduino

// front Ultrasonic
#define echoPin 7 // 7 pin on arduino
#define pingPin 5 // 5 on shift register

// left Ultrasonic
#define echoPinLeft 6 // 6 pin on arduino
#define pingPinLeft 6 // 6 on shift register

// right Ultrasonic
#define echoPinRight 5 // 5 pin on arduino
#define pingPinRight 7 // 7 on shift register

// arm pins on arduino
#define arm_pin 0
#define joint_h_pin 1
#define joint_l_pin 2
#define base_pin 3
#define rotate_pin 4

#define arm_lift_height 10

Servo arm, joint_h, joint_l, base, rotate;

// shift register pins
#define latchPin 12 // Latch pin of 74HC595 is connected to Digital pin 12
#define clockPin 11 // Clock pin of 74HC595 is connected to Digital pin 11
#define dataPin 13  // Data pin of 74HC595 is connected to Digital pin 13

Shifty shift;

bool has_storage = false;

void setup()
{

  shift.setPins(dataPin, clockPin, latchPin);
  shift.setBitCount(8);

  // Set all the motor control pins to outputs
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  // Set Ultrasonic Sensor pins
  pinMode(echoPin, INPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);

  // Turn off motors - Initial state
  shift.writeBit(motorPin1, LOW);
  shift.writeBit(motorPin2, LOW);
  shift.writeBit(motorPin3, LOW);
  shift.writeBit(motorPin4, LOW);

  // // attach arm servos
  // arm.attach(arm_pin);
  // joint_h.attach(joint_h_pin);
  // joint_l.attach(joint_l_pin);
  // base.attach(base_pin);
  // rotate.attach(rotate_pin);

  // check();
  // lift();
  // pick();
  //lower();
}

void loop()
{

  long cm = see();
  if (cm < 7)
  {
    stopm();
    // if (!use_arm())
    {
      speed_control(0);
      move_backward();
      delay(1000);
      turn_left();
      while (cm < 26)
      {
        cm = see();
        delay(100);
      }
    }
  }
  else
  {
    move_forward();
    if (cm < 50)
      speed_control(0);
    else if (cm < 106)
      speed_control((cm - 56) * 2);
    else
      speed_control(100);
  }
  delay(100);
}

void stopm()
{
  shift.writeBit(motorPin1, LOW);
  shift.writeBit(motorPin2, LOW);
  shift.writeBit(motorPin3, LOW);
  shift.writeBit(motorPin4, LOW);
}

void move_forward()
{
  shift.writeBit(motorPin1, HIGH);
  shift.writeBit(motorPin2, LOW);
  shift.writeBit(motorPin3, HIGH);
  shift.writeBit(motorPin4, LOW);
}

void move_backward()
{
  shift.writeBit(motorPin1, LOW);
  shift.writeBit(motorPin2, HIGH);
  shift.writeBit(motorPin3, LOW);
  shift.writeBit(motorPin4, HIGH);
}

void turn_left()
{
  shift.writeBit(motorPin1, HIGH);
  shift.writeBit(motorPin2, LOW);
  shift.writeBit(motorPin3, LOW);
  shift.writeBit(motorPin4, HIGH);
}

void turn_right()
{
  shift.writeBit(motorPin1, LOW);
  shift.writeBit(motorPin2, HIGH);
  shift.writeBit(motorPin3, HIGH);
  shift.writeBit(motorPin4, LOW);
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
  if (!check())
    return false;
  lower();
  delay(500);
  pick();
  delay(500);
  lift();
  delay(500);
  return true;
}

void lower()
{
  rotate.write(35);
  base.write(180);
  joint_l.write(90);
  joint_h.write(180);
  arm.write(180);
}

void pick()
{
  rotate.write(35);
  base.write(180);
  joint_l.write(90);
  joint_h.write(180);
  arm.write(130);
}

void lift()
{
  rotate.write(35);
  base.write(30);
  joint_l.write(120);
  joint_h.write(180);
  arm.write(130);
  has_storage = true;
}

bool check()
{
  // rotate.write(35);

  // if (has_storage)
  //   return false;

  // arm.write(0);
  // if (see_left() >= arm_lift_height && see_right() >= arm_lift_height)
  //   return false;

  // arm.write(90);
  // int l1 = see_left();
  // int r1 = see_right();

  // arm.write(180);
  // if (see_left() <= l1 && see_right() <= r1)
    return false;

  // return true;
}

long see_left()
{
  return see(pingPinLeft, echoPinLeft);
}

long see_right()
{
  return see(pingPinRight, echoPinRight);
}

long see()
{
  return see(pingPin, echoPin);
}

long see(int ping, int echo)
{
  long duration, cm;
  shift.writeBit(ping, LOW);
  delayMicroseconds(2);
  shift.writeBit(ping, HIGH);
  delayMicroseconds(10);
  shift.writeBit(ping, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}