#!/usr/bin/env python
          
      
import time
import serial
import datetime
          
      
ser = serial.Serial(
              
	port='/dev/ttyUSB0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
counter=0
          
      
while 1:
        now = datetime.datetime.now()
        x=ser.readline()
        if x <> "":
        	#print str(now)
                print now.strftime("%Y-%m-%d, %H:%M:%S") +', '+ x 
		#print x
