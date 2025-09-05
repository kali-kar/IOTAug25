import RPi.GPIO as GPIO
import time

# Use BCM pin numbering
GPIO.setmode(GPIO.BCM)

# Define GPIO pins
IR_SENSOR_1 = 23  # GPIO16
IR_SENSOR_2 = 22  # GPIO14
BUZZER = 24       # GPIO18

# Setup pins
GPIO.setwarnings(False)
GPIO.setup(IR_SENSOR_1, GPIO.IN)
GPIO.setup(IR_SENSOR_2, GPIO.IN)
GPIO.setup(BUZZER, GPIO.OUT)

try:
    while True:
        sensor1 = GPIO.input(IR_SENSOR_1)
        sensor2 = GPIO.input(IR_SENSOR_2)

        if sensor1 == 0 or sensor2 == 0:  # Assuming LOW means detection
            GPIO.output(BUZZER, GPIO.HIGH)
            print("Object detected!")
        else:
            GPIO.output(BUZZER, GPIO.LOW)

        time.sleep(0.1)

except KeyboardInterrupt:
    print("Exiting program...")

finally:
    GPIO.cleanup()
