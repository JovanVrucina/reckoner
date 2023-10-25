import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT)
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)


GPIO.output(16, GPIO.HIGH)
GPIO.output(20, GPIO.HIGH)
