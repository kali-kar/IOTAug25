from gpiozero import Button,TrafficLights,Buzzer
from time import sleep
buzzer = Buzzer(15)
lights = TrafficLights(25,8,7)
button = Button(21)
while True:
        button.wait_for_press()
        lights.green.on()
        sleep(1)
        lights.green.off()
       
        lights.green.on()
        lights.red.on()
        sleep(1)
        lights.amber.off()
        lights.green.off()
       
        buzzer.on()
        lights.red.on()
        sleep(1)
        lights.off()
        buzzer.off()
