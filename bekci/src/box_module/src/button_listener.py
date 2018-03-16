#!/usr/bin/env python
import RPi.GPIO as GPIO
from hardware import Led
import time
import rospy
import subprocess
#import os
from box_module.msg import WarningSignal

#global variables for pins
openButton = 18
levelOneButton = 23
levelTwoButton = 24

openLedPin = 17
levelOneLedPin = 27
levelTwoLedPin = 22

buzzerPin = 4

#main function for setting led and button
def setup():
    global openLed
    global levelOneLed
    global levelTwoLed

    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)

    openLed = Led(openLedPin)
    levelOneLed = Led(levelOneLedPin)
    levelTwoLed = Led(levelTwoLedPin)

    GPIO.setup(openButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(levelOneButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(levelTwoButton, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    GPIO.add_event_detect(openButton, GPIO.FALLING, callback=openDriver, bouncetime=300)

    #filePublisher = rospy.Publisher('fileOpener', String, queue_size=10)
    #rospy.init_node('button_talker', anonymous=True)

    print "setup done"

#open button function
def openDriver(sub0):
    print "open buttons"
    if openLed.flag == False:
        driverProcess = subprocess.Popen(["roslaunch ur_modern_driver ur5_bringup.launch robot_ip:= 10.0.0.2"], shell=True, stdout=subprocess.PIPE)
        openLed.open()
        #activate button
        GPIO.add_event_detect(levelOneButton, GPIO.FALLING, callback=levelOneSetup, bouncetime=300)
        GPIO.add_event_detect(levelTwoButton, GPIO.FALLING, callback=levelTwoSetup, bouncetime=300)
    else:
        driverProcess.terminate()

#security level callback functions
def levelOneSetup(sub1):
    print "level one"
    if levelOneLed.flag == False:
        print "inside 1"
        levelOneLed.open()
        levelOneProcess = subprocess.Popen(["roslaunch bekci bekci.launch"], shell=True, stdout=subprocess.PIPE)
        #os.system("roslaunch box_module endUser.launch")
    else:
        print "stop 1"
        #levelOneProcess.terminate()
        levelOneLed.close()

def levelTwoSetup(sub2):
    global levelTwoFlag
    print "level two"
    if levelTwoLed.flag == False:
        print "inside 2"
        levelTwoProcess = subprocess.Popen(["roslaunch box_module endUser.launch"], shell=True, stdout=subprocess.PIPE)
        levelTwoLed.open()
    else:
        print "stop 2"
        #levelTwoProcess.terminate()
        levelTwoLed.close()

#main while loop
try:
   setup()
   while True:
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()       # clean up GPIO on CTRL+C exit
GPIO.cleanup()
