#!/usr/bin/env python
import RPi.GPIO as GPIO
from gpiozero import Buzzer
import time
import rospy
import subprocess
#import os
#from std_msgs.msg import String

#global variables for pins
openButton = 18
levelOneButton = 23
levelTwoButton = 24

levelOneFlag = False
levelTwoFlag = False

openLed = 17
levelOneLed = 27
levelTwoLed = 22

buzzerPin = 4

#function for controlling pins
def openLedFunc(pinNo):
    GPIO.output(pinNo, GPIO.HIGH)
def closeLedFunc(pinNo):
    GPIO.output(pinNo, GPIO.LOW)

#main function for setting led and button
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

    buzzer = Buzzer(buzzerPin)

    #filePublisher = rospy.Publisher('fileOpener', String, queue_size=10)
    #rospy.init_node('button_talker', anonymous=True)

    print "setup done"

#open button function
def openDriver(sub0):
    #driverProcess = subprocess.Popen(["roslaunch box_module endUser.launch"], shell=True, stdout=subprocess.PIPE)
    #filePublisher.publish("driver")
    print "open buttons"
    openLedFunc(openLed) #flash led
    #activate button
    GPIO.add_event_detect(levelOneButton, GPIO.FALLING, callback=levelOneSetup, bouncetime=300)
    GPIO.add_event_detect(levelTwoButton, GPIO.FALLING, callback=levelTwoSetup, bouncetime=300)

#security level callback functions
def levelOneSetup(sub1):
    global levelOneFlag
    print "level one"
    if levelOneFlag == False:
        print "inside 1"
        openLedFunc(levelOneLed)
        #levelOneProcess = subprocess.Popen(["roslaunch box_module endUser.launch"], shell=True, stdout=subprocess.PIPE)
        #os.system("roslaunch box_module endUser.launch")
        #filePublisher.publish("levelone")
        levelOneFlag = True
    else:
        print "stop 1"
        closeLedFunc(levelOneLed)
        levelOneFlag = False

def levelTwoSetup(sub2):
    global levelTwoFlag
    print "level two"
    if levelTwoFlag == False:
        print "inside 2"
        #levelTwoProcess = subprocess.Popen(["roslaunch box_module endUser.launch"], shell=True, stdout=subprocess.PIPE)
        #os.system("roslaunch box_module endUser.launch")
        #filePublisher.publish("leveltwo")
        openLedFunc(levelTwoLed)
        levelTwoFlag = True
    else:
        print "stop 2"
        closeLedFunc(levelTwoLed)
        levelTwoFlag = False

#main while loop
try:
   setup()
   while True:
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()       # clean up GPIO on CTRL+C exit
GPIO.cleanup()
