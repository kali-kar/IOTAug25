# Program to Read Light Status from remote place.

#sudo apt-get install python-flask

import time
import RPi.GPIO as gpio
from flask import Flask, render_template   #Importing Flask
import datetime

app = Flask(__name__)

gpio.setwarnings(False)
gpio.setmode(gpio.BOARD) 

led1 = 13     # pin is connected to LED and it should be OUT
switch1 = 35  # pin is connected to SWITC and it should be IN

gpio.setup(led1,gpio.OUT,initial=1)
gpio.setup(switch1,gpio.IN)

light_status = "OFF"

def glow_led(event):
    print("Entered Here")
    global light_status
    if event == switch1 and light_status == "OFF":
        gpio.output(led1, False)
        light_status = "ON"
            
    elif event == switch1 and light_status == "ON":
        gpio.output(led1, True)
        light_status = "OFF"



@app.route('/') #Route for Turning RedLed On
def ledstatus():
    now = datetime.datetime.now()
    timeString = now.strftime("%H:%M %d-%m-%Y")
    templateData = {
      'status' : light_status,
      'time': timeString
      }
    return render_template('lightstatus.html', **templateData)

gpio.add_event_detect(switch1, gpio.RISING , callback = glow_led, bouncetime = 100)
app.run(debug = True, port = 4000, host='_YOUR_IP')
