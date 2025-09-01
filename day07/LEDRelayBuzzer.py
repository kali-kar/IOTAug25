from gpiozero import LED,Button
from time import sleep

led = LED(17)
relay = LED(23)
buzzer = LED(22)
button = Button(14)

while True:
    
    button.wait_for_press()
    led.on()
    sleep(1)
    led.off()
    
    button.wait_for_press()
    relay.on()
    sleep(1)
    relay.off()
    
    button.wait_for_press()
    buzzer.on()
    sleep(1)
    buzzer.off()
    
    