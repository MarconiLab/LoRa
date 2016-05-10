#!/usr/bin/env python
          
from subprocess import call
from ubidots import ApiClient
import math
import time
import serial
import datetime
import threading


def f1():
	#global uploadfile
	call ([uploadfile], shell=True)
	#call f() again in 60 seconds
	threading.Timer(300, f1).start()

# Create an ApiClient object

api = ApiClient(token='BBTANzYExMFrSdPXlQtbeKXBejtMqo')#irUkxm156raVSyfCQuJakEY47JmtIN

# Here is where you usually put the code to capture the data, either through your GPIO pins or as a calculation. We'll simply put an artificial signal here:
          
      
ser = serial.Serial(
              
	port='/dev/ttyUSB0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

now = datetime.datetime.now()
name_file = 'rssi_'+now.strftime("%Y-%m-%d_%H:%M")+'.txt'
f=open(name_file,'w')          
f.write('Id,Date,Time,Sequence,RSSI_pckt,RSSI,SNR,Lat,Lng\n') 
print 'file created '+ name_file 
f.close() 
#upload file to Dropbox following
#http://raspi.tv/2013/how-to-use-dropbox-with-raspberry-pi
uploadfile = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh upload /home/pi/Dropbox/"+name_file+' '+name_file
try: 
	f1()
except ValueError:
	print "Oops!  "

try:
	while True:
	        now = datetime.datetime.now()
	        x=ser.readline()
		if x <> "":
			x1=x.rstrip()
			print x1
	        	xsep=x1.split(',')  #packet[138,45.7036,,916,-71,-96,10]
			if len(xsep)>2:
				sequence = xsep[0]
				lat = xsep[1]
				lng = xsep[2]
				print lng
				id = xsep[3]
				rssi_pckt = xsep[4]	
				rssi = xsep[5]
				#if int(rssi) >= 0:
				#	int(rssi)=int(-rssi)
				snr = xsep[6]
				data = "Ident="+id+", "+now.strftime("%Y-%m-%d, %H:%M:%S")+", Sequence= "+sequence+", RSSI_pckt= "+rssi_pckt+", RSSI= "+rssi+", SNR= "+snr+", LAT= "+lat+", LNG="+lng
				print data
				f=open(name_file,"a")
				f.write(id+','+now.strftime("%Y-%m-%d,%H:%M:%S")+','+sequence+','+rssi_pckt+','+rssi+','+snr+','+lat+','+lng+'\n')
				f.close() 				
				try:
					response = api.save_collection([
						{'variable': '571896c37625425c573aba7f', 'value': sequence}, #570cb32676254219690076da
	  					{'variable': '571897c47625426435f7ab8a', 'value': rssi},#570cb3387625421a88c4e102
	  					{'variable': '571897d476254263f47d2b0f', 'value': snr},#570cb3307625421a88c4e100'
					 	{'variable': '571897da7625425f32773996', 'value': rssi_pckt},#5714e16d76254235f55e90cd'
						{'variable': '571897e67625426489793d49', 'value': lat},#57178caf7625421ebe231f1f
						{'variable': '571897f3762542658cba0c5e', 'value': 1,'context':{'lat': lat, 'lng': lng}},#57178cbf7625421e6943c5e6
						{'variable': '571897ee76254264eb2616ee', 'value': lng}#57179a3b762542061252639c
					])
					print response
				except: 
  					print 'Error sending to Ubi'
					#f.write("Error sending to Ubi\n")	
					pass
except KeyboardInterrupt:
	print '\nSerial port and file closed'
	ser.close()
	#f.close()  
	call ([uploadfile], shell=True)


  
      
