import serial
import time

ser = serial.Serial('/COM3', baudrate = 9600, timeout = 1)  # open serial port
card = 0

print(ser.name) # check which port was really used
ser.write(b'hello')

#criar conexão do card com o arduíno
#criar conexão do LED com o arduíno
#criar conexão do LCD com o arduíno

def user():
    while True:
        while card == 1:
            #lED R('H')
            #LCD print('Bem vindo [nome]')
            #Turn bay status to occupied
            if card != 1:
            #LED R('L')
            #LED O('H')
            #LCD print('Baía ocupada')
            #Turn user status to "not in the bay"
    else:
         #LED G('H')
         #LCD print('Baía livre para uso')
        
