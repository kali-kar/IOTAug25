import network
import time
import machine
import onewire
import ds18x20
from umqtt.simple import MQTTClient
import ntptime
ntptime.host = 'time.google.com'
# WiFi credentials
WIFI_SSID = 'Raveendra'
WIFI_PASSWORD = '12345678'
wlan=None
# MQTT settings
MQTT_BROKER = 'test.mosquitto.org'
MQTT_PORT = 1883
MQTT_TOPIC = b'esp3201/ds18b2001/temperature'
CLIENT_ID = b'esp32_ds18b20_pub'

# DS18B20 pin
ds_pin = machine.Pin(14)  # Change if using a different GPIO
led = machine.Pin(23, machine.Pin.OUT)
led.off()
# IST offset in seconds (+5 hours 30 minutes)
IST_OFFSET = 5 * 3600 + 30 * 60  # 19800 seconds
def blink(n=1,t=0.5):
    while n:
        led.on()
        time.sleep(t)
        led.off()
        time.sleep(t)
        n-=1
    return        
def wifi_connect():
    try:        
        global wlan
        if wlan == None:
            wlan=network.WLAN(network.STA_IF)
        if not wlan.active():
            wlan.active(True)
        if not wlan.isconnected():
            #print('Connecting to network...')
            wlan.connect(WIFI_SSID, WIFI_PASSWORD)
            while not wlan.isconnected():
                blink(n=1,t=0.2)
    except:
        led.on()
def sync_time():
    try:
        ntptime.settime()
    except Exception as e:
        blink(1)

def get_ist_timestamp():
    # Get current UTC time in seconds since epoch
    utc_time = time.time()
    # Add IST offset
    ist_time = utc_time + IST_OFFSET
    # Convert to struct_time
    t = time.localtime(ist_time)
    # Format: YYYY-MM-DDTHH:MM:SS+05:30
    return "{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}+05:30".format(
        t[0], t[1], t[2], t[3], t[4], t[5]
    )

def read_temp():
    ds_sensor = ds18x20.DS18X20(onewire.OneWire(ds_pin))
    roms = ds_sensor.scan()
    if not roms:
        blink(2)
        return None
    ds_sensor.convert_temp()
    time.sleep_ms(750)
    temp = ds_sensor.read_temp(roms[0])
    return temp

wifi_connect()
sync_time()
client = MQTTClient(CLIENT_ID, MQTT_BROKER, port=MQTT_PORT)
if wlan.isconnected():
    client.connect()

try:
    while True:
        temperature = read_temp()
        timestamp = get_ist_timestamp()
        if temperature is not None:
            msg = '{{"timestamp":"{}","temperature":{:.2f}}}'.format(timestamp, temperature)
            if wlan.isconnected():
                client.publish(MQTT_TOPIC, msg)
                led.on()
            else:
                while not wlan.isconnected():
                    wifi_connect()
                client.connect()
        else:
            blink(2)
        time.sleep(5)
        led.off()
        time.sleep(5)
except KeyboardInterrupt:
    led.off()
finally:
    client.disconnect()

"""
# Copy of board program
import network
import time
import machine
import onewire
import ds18x20
from umqtt.simple import MQTTClient
import ntptime
ntptime.host = 'time.google.com'
# WiFi credentials
WIFI_SSID = 'Raveendra'
WIFI_PASSWORD = '12345678'
wlan=None
# MQTT settings
MQTT_BROKER = 'test.mosquitto.org'
MQTT_PORT = 1883
MQTT_TOPIC = b'esp3201/ds18b2001/temperature'
CLIENT_ID = b'esp32_ds18b20_pub'

# DS18B20 pin
ds_pin = machine.Pin(14)  # Change if using a different GPIO
led = machine.Pin(23, machine.Pin.OUT)
led.off()
# IST offset in seconds (+5 hours 30 minutes)
IST_OFFSET = 5 * 3600 + 30 * 60  # 19800 seconds
def blink(n=1,t=0.5):
    while n:
        led.on()
        time.sleep(t)
        led.off()
        time.sleep(t)
        n-=1
    return        
def wifi_connect():
    try:        
        global wlan
        if wlan == None:
            wlan=network.WLAN(network.STA_IF)
        if not wlan.active():
            wlan.active(True)
        if not wlan.isconnected():
            #print('Connecting to network...')
            wlan.connect(WIFI_SSID, WIFI_PASSWORD)
            while not wlan.isconnected():
                blink(n=1,t=0.2)
    except:
        led.on()
def sync_time():
    try:
        ntptime.settime()
    except Exception as e:
        blink(1)

def get_ist_timestamp():
    # Get current UTC time in seconds since epoch
    utc_time = time.time()
    # Add IST offset
    ist_time = utc_time + IST_OFFSET
    # Convert to struct_time
    t = time.localtime(ist_time)
    # Format: YYYY-MM-DDTHH:MM:SS+05:30
    return "{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}+05:30".format(
        t[0], t[1], t[2], t[3], t[4], t[5]
    )

def read_temp():
    ds_sensor = ds18x20.DS18X20(onewire.OneWire(ds_pin))
    roms = ds_sensor.scan()
    if not roms:
        blink(2)
        return None
    ds_sensor.convert_temp()
    time.sleep_ms(750)
    temp = ds_sensor.read_temp(roms[0])
    return temp

wifi_connect()
sync_time()
client = MQTTClient(CLIENT_ID, MQTT_BROKER, port=MQTT_PORT)
if wlan.isconnected():
    client.connect()

try:
    while True:
        temperature = read_temp()
        timestamp = get_ist_timestamp()
        if temperature is not None:
            msg = '{{"timestamp":"{}","temperature":{:.2f}}}'.format(timestamp, temperature)
            if wlan.isconnected():
                client.publish(MQTT_TOPIC, msg)
                led.on()
            else:
                while not wlan.isconnected():
                    wifi_connect()
                client.connect()
        else:
            blink(2)
        time.sleep(5)
        led.off()
        time.sleep(5)
except KeyboardInterrupt:
    led.off()
finally:
    client.disconnect()



"""
