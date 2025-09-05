import time, datetime
import RPi.GPIO as GPIO
import telepot
from telepot.loop import MessageLoop
 
led = 26
now = datetime.datetime.now()
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
 #LED
GPIO.setup(led, GPIO.OUT)
GPIO.output(led, 0) #Off initially
def action(msg):
    chat_id = msg['chat']['id']
    command = msg['text']
 
    print 'Received: %s' % command
 
    if 'on' in command:
        message = "Turned on "
        if 'led' in command:
            message = message + "led"
            GPIO.output(led, 1)
            telegram_bot.sendMessage (chat_id, message)
 
    if 'off' in command:
        message = "Turned off "
        if 'led' in command:
            message = message + "led "
            GPIO.output(led, 0)
            
          
        telegram_bot.sendMessage (chat_id, message)
 
 telegram_bot = telepot.Bot('672697023:AAGcffy2mXLdUSflVaF_LqBRxfxZsjmAJkI')
print (telegram_bot.getMe())
 
