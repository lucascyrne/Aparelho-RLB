import serial
import time

read = serial.Serial("COM7", baudrate=9600, timeout=1)

while 1:
	read.write(b"...")
	print(str(read.readline())).decode(encoding='UTF-8',errors='strict')
