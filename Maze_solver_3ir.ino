#include <AFMotor.h>

// Motor shield initialization
AF_DCMotor motor1(3); // Motor connected to M3
AF_DCMotor motor2(4); // Motor connected to M4

// IR sensor pins
const int leftSensorPin = 11;  // Digital pin for the left IR sensor
const int middleSensorPin = 9; // Digital pin for the middle IR sensor
const int rightSensorPin = 2; // Digital pin for the right IR sensor

// IR sensor thresholds
const int leftThreshold = 700;  // Adjust this value for the left sensor
const int rightThreshold = 700; // Adjust this value for the right sensor

// Motor speeds
const int forwardSpeed = 200;   // Speed for forward movement
const int turnSpeed = 150;      // Speed for turning

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set up the motor pins
  motor1.setSpeed(forwardSpeed);
  motor2.setSpeed(forwardSpeed);
}

void loop() {
  int IR1 = digitalRead(leftSensorPin);
  int IR2 = digitalRead(middleSensorPin);
  int IR3 = digitalRead(rightSensorPin);

  // Print IR sensor values for debugging
  Serial.print("Left sensor: ");
  Serial.print(IR1);
  Serial.print(" | Middle sensor: ");
  Serial.println(IR2);
  Serial.print(" | Right sensor: ");
  Serial.println(IR3);

  if (IR1 == LOW && IR2 == HIGH && IR3 == LOW)//Straight path
    {
     Forward();
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == LOW)//Left turn
    {
     Left();
    }

  if (IR1 == LOW && IR2 == LOW && IR3 == HIGH)//Right Turn
    {
      Right();
    }

  if (IR1 == HIGH && IR2 == LOW && IR3 == HIGH)//T Intersection
    {
      Left(); // As left is possible
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == LOW)//Left T Intersection
    {
      Left();// As Left is possible
    }

  if (IR1 == LOW && IR2 == HIGH && IR3 == HIGH)//Right T Tntersection
    {
     Forward();//As Straight path is possible
    }

  if (IR1 == LOW && IR2 ==LOW && IR3 == LOW)//Dead End
    {
     Right(); //As no other direction is possible        nnnnnnnnn
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//4 Lane intersection
    {
     Left(); //As no other direction is possible
    }

  if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH)//End of Maze
    {
     Stop(); //As no other direction is possible
    } 
}

void Forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void Right() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(500); // Adjust this value for desired turning time
}

void Left() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(500); // Adjust this value for desired turning time
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
