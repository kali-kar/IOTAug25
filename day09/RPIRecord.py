import os
import datetime
import sys
import time
import subprocess

current_dir = os.path.dirname(__file__)
print(current_dir)
current_date = datetime.datetime.now().strftime('%d-%m-%Y\%H:%M:%S')
image_path = os.path.join('/home/pi/Desktop/team1/images',current_date+'.h264')
print(image_path)
os.system('raspivid -o ' + image_path + ' -t 10000')
print("Video Captured")
time.sleep(5) #change it to the disired duration of the video