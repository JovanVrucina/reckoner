import sys
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)

if(sys.argv[1] == 'L'):
    GPIO.output(16, GPIO.HIGH)
    GPIO.output(20, GPIO.LOW)
elif(sys.argv[1] =='R'):
    GPIO.output(20, GPIO.HIGH)
    GPIO.output(16, GPIO.LOW)
elif(sys.argv[1]=='F'):
    GPIO.output(16, GPIO.HIGH)
    GPIO.output(20, GPIO.HIGH)
elif(sys.argv[1]=='S'):
    GPIO.output(16, GPIO.LOW)
GPIO.output(20, GPIO.LOW)