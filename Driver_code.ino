#include <AFMotor.h>

// Create an instance of the Adafruit Motor Shield library
AF_DCMotor motor3(3);  // Motor connected to M3
AF_DCMotor motor4(4);  // Motor connected to M4

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Set motor speed
  motor3.setSpeed(255);  // Set maximum speed for motor3
  motor4.setSpeed(255);  // Set maximum speed for motor4
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'L') {
      turnLeft();
    } else if (command == 'R') {
      turnRight();
    } else if (command == 'S') {
      stop();
    }
  }
}




void moveForward() {
  Serial.println("Moving Forward");
  motor3.run(FORWARD);  // Motor3 rotates forward
  motor4.run(FORWARD);  // Motor4 rotates forward
}

void moveBackward() {
  Serial.println("Moving Backward");
  motor3.run(BACKWARD);  // Motor3 rotates backward
  motor4.run(BACKWARD);  // Motor4 rotates backward
}

void turnLeft() {
  Serial.println("Turning Left");
  motor3.run(BACKWARD);  // Motor3 rotates backward
  motor4.run(FORWARD);   // Motor4 rotates forward
}

void turnRight() {
  Serial.println("Turning Right");
  motor3.run(FORWARD);   // Motor3 rotates forward
  motor4.run(BACKWARD);  // Motor4 rotates backward
}

void stop(){
  Serial.println("Stopping");
  motor3.run(RELEASE);   // Release motor3
  motor4.run(RELEASE);   // Release motor4
}

