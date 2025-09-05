PiCamera
from picamera import PiCamera
from time import sleep
import datetime
camera = PiCamera()
camera.start_preview()
current_date=datetime.datetime.now().strftime('%d-%m-%Y%H:%M:%S')
sleep(5)
camera.capture('/home/pi/Desktop/team1/images/'+current_date+'.jpg')
camera.stop_preview()
print("Image captured")
