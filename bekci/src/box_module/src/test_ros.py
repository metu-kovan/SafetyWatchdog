#!/usr/bin/env python
import rospy
import sys
import os

def main(args):

	name = raw_input("Enter your name: ")
	print "You entered: " + name
	if name == 'end':
		os.system("roslaunch box_module endUser.launch")

if __name__ == '__main__':
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        print "You hit control-c"
