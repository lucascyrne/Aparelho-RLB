import serial

read = serial.Serial ("COM1", baudrate=9600, timeout=1)
while 1:
	read.write(b"...")
	print(str(read.readline())) 
