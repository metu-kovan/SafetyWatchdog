#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

class Led:
    def __init__ (self, pin):
        self.pinNo = pin
        GPIO.setup(self.pinNo,GPIO.OUT)
        self.flag = False
        self.close()

    def open(self):
        GPIO.output(self.pinNo, GPIO.HIGH)
        self.flag = True
    def close(self):
        GPIO.output(self.pinNo, GPIO.LOW)
        self.flag = False

    def warning(self, min):
        self.open()
        time.sleep(min)
        self.close()
        time.sleep(min)

class Buzzer:
    def __init__ (self, pin):
        self.pinNo = pin
        GPIO.setup(self.pinNo,GPIO.OUT)
        self.flag = False
        self.close()

    def open(self):
        GPIO.output(self.pinNo, GPIO.LOW)
        self.flag = True

    def close(self):
        GPIO.output(self.pinNo, GPIO.HIGH)
        self.flag = False

    def warning(self, min):
        self.open()
        time.sleep(min)
        self.close()
        time.sleep(min)
