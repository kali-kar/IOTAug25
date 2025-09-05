ThingSpeakDHT11

import Adafruit_DHT
import requests
import time

# ThingSpeak channel details
channel_id = _YOUR_CHANNEL_ID_ #change the channel id 
write_key = '_YOUR_WRITE_KEY'  #change the write key 
url = 'https://api.thingspeak.com/update'

# Sensor setup
sensor = Adafruit_DHT.DHT11
gpio_pin = 4  # GPIO pin connected to DHT11

while True:
    humidity, temperature = Adafruit_DHT.read_retry(sensor, gpio_pin)

    if humidity is not None and temperature is not None:
        print(f"Temperature: {temperature:.1f}°C  Humidity: {humidity:.1f}%")

        # Send data to ThingSpeak
        payload = {
            'api_key': write_key,
            'field1': temperature,
            'field2': humidity
        }

        try:
            response = requests.post(url, data=payload)
            if response.status_code == 200:
                print("Data sent successfully!")
            else:
                print(f"Failed to send data. HTTP {response.status_code}")
        except Exception as e:
            print(f"Error sending data: {e}")
    else:
        print("Sensor read failed. Check wiring or sensor.")

    time.sleep(10)  # Wait before next reading
