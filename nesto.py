import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)


GPIO.output(16, GPIO.HIGH)
GPIO.output(20, GPIO.HIGH)

time.sleep(3)

left = True

while(True):
	if(left):
		GPIO.output(16, GPIO.HIGH)
		GPIO.output(20, GPIO.LOW)
		left = False
		time.sleep(1)
	else:
		GPIO.output(16, GPIO.LOW)
		GPIO.output(20, GPIO.HIGH)
		left = True
		time.sleep(1)
	GPIO.output(16, GPIO.HIGH)
	GPIO.output(20, GPIO.HIGH)
	time.sleep(5)
