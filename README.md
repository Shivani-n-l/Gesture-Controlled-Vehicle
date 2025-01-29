# 🚗 Gesture-Controlled-Vehicle
Hand Gesture Controlled Vehicle using Arduino, Bluetooth, and OpenCV

This repository contains code and resources for building a hand gesture-controlled vehicle. The system uses computer vision for gesture recognition and Arduino to control the vehicle's movement, along with obstacle detection for safety.

## Features
- **Real-time hand gesture detection** using OpenCV and the cvzone library.
- **Obstacle detection** to avoid collisions using an ultrasonic sensor.
- **Serial communication** for transmitting commands between Python and Arduino.
- **Gesture-based vehicle control**:
  - **1 Finger Extended**: Move Forward
  - **2 Fingers Extended**: Turn Left
  - **3 Fingers Extended**: Turn Right
  - **4 Fingers Extended**: Move Backward
  - **No Fingers Extended**: Stop


## Repository Structure
- `Hand_Detection.py`: Python script for gesture detection and serial communication with the Arduino.
- `Driver_code.ino`: Arduino code for:
  - Processing commands from the Python program.
  - Controlling the motors.
  - Monitoring the ultrasonic sensor for obstacle detection.

### Hardware Requirements
1. Arduino board (e.g., Arduino Uno)
2. Motor driver module (e.g., L298N)
3. Motors and chassis for the vehicle
4. Ultrasonic sensor (e.g., HC-SR04) for obstacle detection
5. Webcam for hand gesture recognition
6. Computer with Python installed

### Software Requirements
- Python 3.8+
- Required Python libraries:
  - `opencv-python`
  - `cvzone`
  - `mediapipe`
  - `matplotlib`
  - `pyserial`
- Arduino IDE for uploading the driver code.

## How to Run
1. Connect the Arduino to your computer via USB. 
2. Upload the Driver_Code.ino to the Aurdino.
3. Open `Hand_Detection.py` and update the serial port (`COM5`) if necessary.
4. Run the Python script:
   ```bash
   python Hand_Detection.py
   ```
5. Use hand gestures to control the vehicle:
   - The system will stop automatically if an obstacle is detected.
  
## Troubleshooting
- Verify the correct COM port is specified in `Hand_Detection.py`.
- Ensure the ultrasonic sensor is connected properly.
- Adjust the detection confidence in the Python script if gestures are not recognized reliably.
- Test the ultrasonic sensor using basic Arduino code to ensure it's functioning.
