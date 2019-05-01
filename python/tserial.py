import serial 

ser= serial.Serial("/dev/tty/USB0", baudrate= 9600, timeout=1)

while 1:
	arduinodata = ser.readline().decode("ascii")
	print(arduinodata)
