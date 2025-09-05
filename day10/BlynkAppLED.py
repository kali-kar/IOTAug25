import blynklib
from gpiozero import LED
from signal import pause

# Blynk authorization token
BLYNK_AUTH = '_AUTH-TOKEN_'

# GPIO pin where the LED is connected
LED_PIN = 17

# Initialize LED using gpiozero
led = LED(LED_PIN)

# Initialize Blynk
blynk = blynklib.Blynk(BLYNK_AUTH)

# Define handler for virtual pin V0
@blynk.handle_event('write V0')
def write_virtual_pin_handler(pin, value):
    if int(value[0]) == 1:
        led.on()
        print("LED ON")
    else:
        led.off()
        print("LED OFF")

# Main loop
try:
    while True:
        blynk.run()
except KeyboardInterrupt:
    print("\nExiting program...")
