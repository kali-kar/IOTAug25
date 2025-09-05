import time
from gpiozero import LED, OutputDevice
import telepot
from telepot.loop import MessageLoop


led = LED(15)             # LED on GPIO 15
relay = OutputDevice(18)  # Relay on GPIO 18

led.off()
relay.off()

# Bot Tokens (replace with your actual tokens)
LED_BOT_TOKEN = '_BOT1_API'
RELAY_BOT_TOKEN = '_BOT2_API'

#  Initialize bots
led_bot = telepot.Bot(LED_BOT_TOKEN)
relay_bot = telepot.Bot(RELAY_BOT_TOKEN)

print("LED Bot initialized:", led_bot.getMe()['username'])
print("Relay Bot initialized:", relay_bot.getMe()['username'])

#  LED Bot Handler
def handle_led(msg):
    chat_id = msg['chat']['id']
    command = msg['text'].lower()
    print(f"[LED Bot] Received: {command}")

    if 'on' in command and 'led' in command:
        led.on()
        led_bot.sendMessage(chat_id, " LED is ON")
    elif 'off' in command and 'led' in command:
        led.off()
        led_bot.sendMessage(chat_id, "LED is OFF")
    else:
        led_bot.sendMessage(chat_id, "Use 'on led' or 'off led'.")

# Relay Bot Handler
def handle_relay(msg):
    chat_id = msg['chat']['id']
    command = msg['text'].lower()
    print(f"[Relay Bot] Received: {command}")

    if 'on' in command and 'relay' in command:
        relay.on()
        relay_bot.sendMessage(chat_id, " Relay is ON")
    elif 'off' in command and 'relay' in command:
        relay.off()
        relay_bot.sendMessage(chat_id, " Relay is OFF")
    else:
        relay_bot.sendMessage(chat_id, "Use 'on relay' or 'off relay'.")

#  Start both bots
MessageLoop(led_bot, handle_led).run_as_thread()
MessageLoop(relay_bot, handle_relay).run_as_thread()

print("Both bots are running...")

# Keep the script alive
while True:
    time.sleep(10)
