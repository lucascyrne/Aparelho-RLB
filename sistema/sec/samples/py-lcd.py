import serial
import time

s = serial.Serial(11, 9600) #port is 11 (for COM12, and baud rate is 9600
time.sleep(2)    #wait for the Serial to initialize
s.write('Ready...')
while True:
    str = raw_input('Enter text: ')
    str = str.strip()
    if str == 'exit' :
        break
    s.write(str)
