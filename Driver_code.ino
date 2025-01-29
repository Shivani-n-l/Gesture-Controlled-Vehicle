#include <AFMotor.h>
#include <NewPing.h>  

#define TRIGGER_PIN 10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 9      // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Create an instance of the Adafruit Motor Shield library
AF_DCMotor motor3(3);  // Motor connected to M3
AF_DCMotor motor4(4);  // Motor connected to M4

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);     // Initialize Serial Monitor
  
  // Set motor speed
  motor3.setSpeed(255);  // Set maximum speed for motor3
  motor4.setSpeed(255);  // Set maximum speed for motor4
}

void loop() {
  int distance = sonar.ping_cm(); // Get distance from the ultrasonic sensor in cm

  if (distance > 0 && distance < 10) { // If an obstacle is detected within 20 cm
    //Serial.println("Obstacle detected! Turning left...");
    stop();
    delay(500);
    moveBackward();
    delay(500);
    turnLeft(); // Turn left
    delay(1000); // Wait for 1 second
  } else {
    if (Serial.available() > 0) {   // Check if data is available from Bluetooth module
      char command = Serial.read();  // Read the command from Bluetooth module
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
