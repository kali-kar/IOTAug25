import time
import datetime
from gpiozero import LED
import RPi.GPIO as GPIO
import telepot
from telepot.loop import MessageLoop

# Setup
led =LED(15)
now = datetime.datetime.now()

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(led, GPIO.OUT)
GPIO.output(led, 0)  # LED off initially

# Telegram Bot Token
telegram_bot = telepot.Bot('_API-ID_')
print(telegram_bot.getMe())

# Message handler
def action(msg):
    chat_id = msg['chat']['id']
    command = msg['text']

    print('Received: %s' % command)

    if 'on' in command:
        message = "Turned on "
        if 'led' in command:
            message += "led"
            GPIO.setup(led, 1)
            led.on()
        telegram_bot.sendMessage(chat_id, message)

    elif 'off' in command:
        message = "Turned off "
        if 'led' in command:
            message += "led"
            GPIO.setup(led, 0)
            led.off()
        telegram_bot.sendMessage(chat_id, message)

# Start message loop
MessageLoop(telegram_bot, action).run_as_thread()
print('Up and Running....')

# Keep the program running
while True:
    time.sleep(10)
                                                                                                            