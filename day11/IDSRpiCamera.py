import RPi.GPIO as GPIO
from picamera import PiCamera
import time
import smtplib
import os
import logging
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.text import MIMEText

# Logging setup
logging.basicConfig(filename='/home/pi/security/error.log', level=logging.INFO,
                    format='%(asctime)s:%(levelname)s:%(message)s')

print("🔧 Initializing system...")

# Email setup
FROM_ADDR = "************"
TO_ADDR = "XXXXXXXXXXXXXXXXXXXXXx"
APP_PASSWORD = "XXXX XXXX XXXX XXXX"

# GPIO setup
LED = 15
PIR = 12
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED, GPIO.OUT)
GPIO.setup(PIR, GPIO.IN)

print("📡 GPIO setup complete.")
logging.info("GPIO setup complete.")

# Camera setup
try:
    camera = PiCamera()
    camera.rotation = 180
    camera.awb_mode = 'auto'
    camera.brightness = 55
    print("📷 Camera initialized.")
    logging.info("Camera initialized.")
except Exception as e:
    logging.error(f"Camera initialization failed: {e}")
    raise SystemExit("Camera failed to initialize.")

def send_email(filename):
    try:
        print("📤 Sending email...")
        msg = MIMEMultipart()
        msg['From'] = FROM_ADDR
        msg['To'] = TO_ADDR
        msg['Subject'] = "Motion Detected"
        msg.attach(MIMEText("Motion detected. See attached image.", 'plain'))

        with open(filename, 'rb') as img:
            msg.attach(MIMEImage(img.read()))

        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(FROM_ADDR, APP_PASSWORD)
        server.sendmail(FROM_ADDR, TO_ADDR, msg.as_string())
        server.quit()
        print("✅ Email sent.")
        logging.info("Email sent successfully.")
    except Exception as e:
        logging.error(f"Failed to send email: {e}")
        print("❌ Email sending failed.")

def capture_image():
    try:
        timestamp = time.strftime("capture_%Y-%m-%d_%H-%M-%S")
        filename = f"/home/pi/security/{timestamp}.jpg"
        os.makedirs(os.path.dirname(filename), exist_ok=True)
        print(f"📸 Capturing image: {filename}")
        camera.capture(filename)
        logging.info(f"Image captured: {filename}")
        send_email(filename)
    except Exception as e:
        logging.error(f"Image capture or email failed: {e}")
        print("❌ Image capture or email failed.")

# Main loop
print("🚀 System armed. Monitoring for motion...")
logging.info("System started. Monitoring for motion.")

try:
    while True:
        try:
            if GPIO.input(PIR):
                print("🚨 Motion detected!")
                logging.info("Motion detected.")
                GPIO.output(LED, GPIO.HIGH)
                capture_image()
                time.sleep(10)
            else:
                GPIO.output(LED, GPIO.LOW)
            time.sleep(0.5)
        except Exception as loop_error:
            logging.error(f"Error in main loop: {loop_error}")
            print("⚠️ Error in main loop.")
except KeyboardInterrupt:
    GPIO.cleanup()
    camera.close()
    print("🛑 Program terminated by user.")
    logging.info("Program terminated by user.")
except Exception as e:
    logging.error(f"Unexpected error: {e}")
    GPIO.cleanup()
    camera.close()
    print("❌ Unexpected error occurred.")