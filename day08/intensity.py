import RPi.GPIO as GPIO
import time
LED_PIN = 18
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN,GPIO.OUT)
pwm = GPIO.PWM(LED_PIN,100)
pwm.start(0)

try:
    while True:
        GPIO.setwarnings(False)
        for dc in range(0,101,1):
            pwm.ChangeDutyCycle(dc)
            time.sleep(0.01)
        for dc in range(100,-1,-1):
            pwm.ChangeDutyCycle(dc)
            time.sleep(0.01)
except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()
    print("Program stopped and GPIO cleaned up.")
