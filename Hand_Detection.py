import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector
import serial
import time
import mediapipe as mp
import matplotlib.pyplot as plt


# Open serial port
ser = serial.Serial('COM5', 9600)  # Adjust port and baud rate as needed

# Function to send commands to Arduino
def send_command(command,serial_port):
    ser.write(command.encode())
    time.sleep(0.1)  # Add a small delay to ensure Arduino receives the command


# Function to detect and track finger signs
def detect_finger_signs(frame, detector):
    # Find hand landmarks
    hands, _ = detector.findHands(frame)

    if hands:
        hand = hands[0]  # considering the first detected hand

        # Get landmarks of the hand
        landmarks = hand["lmList"]

        # Determine the number of extended fingers
        extended_fingers = 0
        for finger in [8, 12, 16, 20]:  #  index finger, middle finger, ring finger, little finger
                if landmarks[finger][1] < landmarks[finger - 1][1]:  # Check if the finger is extended
                    extended_fingers += 1


        # Determine the finger sign based on the number of extended fingers
        label = ""
        if extended_fingers == 1:
            label = "Forward"
            send_command('F', ser)  # Move forward
        elif extended_fingers == 2:
            label = "Left"
            send_command('L', ser)  # Move left
        elif extended_fingers == 3:
            label = "Right"
            send_command('R', ser)  # Move right
        elif extended_fingers == 4:
            label = "Backward"
            send_command('B', ser)  # Move backward
        elif extended_fingers == 0:
            label = "Stop"
            send_command('S', ser)  # Stop
        x, y = landmarks[9][0], landmarks[9][1]  # Assuming index finger landmark is used for positioning
        cv2.putText(frame, label, (x, y - 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 255), 2)

    return frame


# Initialize HandDetector
detector = HandDetector(detectionCon=0.8)

# Open webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Detect and track hand gestures
    frame = detect_finger_signs(frame, detector)

    # Display the resulting frame
    cv2.imshow('Hand Gesture Control', frame)

    # Break the loop when 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()

# Close serial port when done
ser.close()
