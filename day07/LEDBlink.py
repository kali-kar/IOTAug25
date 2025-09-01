from gpiozero import LED
from time import sleep
led=LED(17)
led1=LED(27)
led2=LED(22)
led3=LED(14)
led4=LED(15)
led5=LED(18)
while True:
    led.on()
    sleep(0.5)
    led.off()
    led1.on()
    sleep(0.5)
    led1.off()
   
    led3.on()
    sleep(0.5)
    led3.off()
   
    led4.on()
    sleep(0.5)
    led4.off()
   
    led5.on()
    sleep(0.5)
    led5.off()