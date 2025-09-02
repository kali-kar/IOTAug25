import RPi.GPIO as GPIO
import time
import datetime
led = 13 #P15
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(led, GPIO.OUT) #Initialising GPIO pins as output
GPIO.setup(led,GPIO.OUT,initial=1)
from flask import Flask, render_template #Importing Flask
app = Flask(__name__)#creates the Flask instance,__name__ is the current python module
                     #the app needs to know where its located to set up some paths.__name__ is just convienent way to get the import name of the place app is defined.
                     #Flask uses the import name to know where to lookup resources,templetes,static files,instance folder etc.
 
@app.route('/') #Simple Hello World Route
def hello_world():
    return render_template('web.html')
   
@app.route('/redledon') #Route for Turning RedLed On
def redledon():
   
    GPIO.output(13, GPIO.LOW) #Turning Pin 31 --> Red Led HIGH
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M")
    templateData = {
      'status' : 'ON',
      'time': timeString
      }
    return render_template('web.html', **templateData)
@app.route('/redledoff') #Route for Turning RedLed Off
def redledoff():
    GPIO.output(13, GPIO.HIGH)  #Turning Pin 31 --> Red Led LOW
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M")
    templateData = {
      'status' : 'OFF',
      'time': timeString
      }
    return render_template('web.html', **templateData)
if __name__ == "__main__":
    app.run(debug = True, port = 5000, host='127.0.0.1')#start our server with port and ip