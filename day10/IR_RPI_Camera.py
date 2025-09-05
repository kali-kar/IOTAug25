import RPi.GPIO as GPIO
from picamera import PiCamera
from time import sleep
import datetime
import os

# Setup
GPIO.setmode(GPIO.BCM)
IR_SENSOR = 23  # GPIO pin for IR sensor
GPIO.setup(IR_SENSOR, GPIO.IN)

camera = PiCamera()

try:
    print("Waiting for object detection...")
    while True:
        if GPIO.input(IR_SENSOR) == 0:  # Assuming LOW means detection
            print("Object detected! Capturing image...")
            current_date = datetime.datetime.now().strftime('%d-%m-%Y_%H-%M-%S')
            image_path = f'/home/pi/Desktop/team1/images/{current_date}.jpg'

            camera.start_preview()
            sleep(2)  # Let camera adjust to lighting
            camera.capture(image_path)
            camera.stop_preview()

            print(f"Image captured: {image_path}")

            # Display the image
            os.system(f'feh {image_path}')
            sleep(5)  # Wait before checking again

except KeyboardInterrupt:
    print("Program interrupted by user.")

finally:
    GPIO.cleanup()
