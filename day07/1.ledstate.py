from gpiozero import LED,Button
from time import sleep
led=LED(17)
led1=LED(27)
button=Button(2)

while True:

    button.wait_for_press()
    led.on()
    sleep(1)
    button.wait_for_press()
    led.off()
    button.wait_for_press()
   
   
    led1.on()
    sleep(1)
    button.wait_for_press()
    led1.off()