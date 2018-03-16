import RPi.GPIO as GPIO
import time
import rospy
import os


openButton = 18
levelOneButton = 23
levelTwoButton = 24

levelOneFlag = False
levelTwoFlag = False

openLed = 17
levelOneLed = 27
levelTwoLed = 22

def high(pinNo):
    GPIO.output(pinNo, GPIO.HIGH)
def low(pinNo):
    GPIO.output(pinNo, GPIO.LOW)

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(openLed,GPIO.OUT)
    GPIO.setup(levelOneLed,GPIO.OUT)
    GPIO.setup(levelTwoLed,GPIO.OUT)

    GPIO.setup(openButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(levelOneButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(levelTwoButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    GPIO.add_event_detect(openButton, GPIO.FALLING, callback=openDriver, bouncetime=300)

    #set all closed at default
    GPIO.output(openLed, GPIO.LOW)
    GPIO.output(levelOneLed, GPIO.LOW)
    GPIO.output(levelTwoLed, GPIO.LOW)

    print "setup done"

def openDriver(sub0):
    print "open buttons"
    high(openLed)
    GPIO.add_event_detect(levelOneButton, GPIO.FALLING, callback=levelOneSetup, bouncetime=300)
    GPIO.add_event_detect(levelTwoButton, GPIO.FALLING, callback=levelTwoSetup, bouncetime=300)

def levelOneSetup(sub1):
    global levelOneFlag
    print "level one"
    if levelOneFlag == False:
        print "inside 1"
        high(levelOneLed)
        os.system("roslaunch box_module endUser.launch")
        levelOneFlag = True
    else:
        print "stop 1"
        low(levelOneLed)
        levelOneFlag = False

def levelTwoSetup(sub2):
    global levelTwoFlag
    print "level two"
    if levelTwoFlag == False:
        print "inside 2"
        os.system("roslaunch box_module endUser.launch")
        high(levelTwoLed)
        levelTwoFlag = True
    else:
        print "stop 2"
        low(levelTwoLed)
        levelTwoFlag = False

try:
   setup()
   while True:
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()       # clean up GPIO on CTRL+C exit
GPIO.cleanup()
