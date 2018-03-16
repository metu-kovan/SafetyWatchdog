
#blink
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

while (True):
    GPIO.output(18, True)
    time.sleep(0.5)
    GPIO.output(18, False)
    time.sleep(0.5)

# led on then off after some time
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23,GPIO.OUT)
print "LED on"
GPIO.output(23,GPIO.HIGH)
time.sleep(1)
print "LED off"
GPIO.output(23,GPIO.LOW)

#button wiwth led on then off
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)


while True:
    input_state = GPIO.input(18)
    if input_state == False:
        print "LED on"
        GPIO.output(23,GPIO.HIGH)
        time.sleep(1)
        print "LED off"
        GPIO.output(23,GPIO.LOW)
        time.sleep(0.2)

#try to add warning state led work buzzer dont

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(17, GPIO.OUT)
GPIO.output(17, GPIO.HIGH)
print "setup done"

while True:
    input_state = GPIO.input(18)
    if input_state == False:
        print "Warning"
        GPIO.output(23, GPIO.HIGH)
        GPIO.output(17, GPIO.LOW)
        time.sleep(0.5)
        GPIO.output(23, GPIO.LOW)
        GPIO.output(17, GPIO.HIGH)
        time.sleep(0.5)
    else:
        GPIO.output(23, GPIO.LOW)
        GPIO.output(17, GPIO.HIGH)
