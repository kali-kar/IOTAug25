import time
import Adafruit_DHT
sensor=Adafruit_DHT.DHT11
pin=4 #connect pin four to collect data verify with the datasheet
while(1):
    try:
        humidity,temperature=Adafruit_DHT.read_retry(sensor,pin)
        print("Humidity="+str(humidity))
        print("Temprature="+str(temperature))
    except ValueError:
        print("Unable to read data")