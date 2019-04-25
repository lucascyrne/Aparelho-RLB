# -*- coding: utf-8 -*-
"""
Created on Thu Apr 25 14:48:01 2019

@author: Aluno
"""

import serial
import serial.tools.list_ports;
import sys
import glob
import serial


##def serial_ports():
##    """ Lists serial port names
##
##        :raises EnvironmentError:
##            On unsupported or unknown platforms
##        :returns:
##            A list of the serial ports available on the system
##    """
##    if sys.platform.startswith('win'):
##        ports = ['COM%s' % (i + 1) for i in range(256)]
##    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
##        # this excludes your current terminal "/dev/tty"
##        ports = glob.glob('/dev/tty[A-Za-z]*')
##    elif sys.platform.startswith('darwin'):
##        ports = glob.glob('/dev/tty.*')
##    else:
##        raise EnvironmentError('Unsupported platform')
##
##    result = []
##    for port in ports:
##        try:
##            s = serial.Serial(port)
##            s.close()
##            result.append(port)
##        except (OSError, serial.SerialException):
##            pass
##    return result
##
##
##if __name__ == '__main__':
##    print(serial_ports())

def get_ports():

    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def findArduino(portsFound):

    commPort = 'None'
    numConnection = len(portsFound)

    for i in range(0, numConnection):
        port = foundPorts[i]
        strPort = str(port)

        if 'Arduino' in strPort:
            splitPort = strPort.split(' ')
            commPort = (splitPort[0])

    return commPort

foundPorts = get_ports()
connectPort = findArduino(foundPorts)

if connectPort != 'None':
    ser = serial.Serial(connectPort, baudrate = 9600, timeout = 1)
    print('Connected to ' + connectPort)

else:
    print('Connection Issue!')

print('DONE')
    

#pegar na lista o primeiro port e aplicar no serial.Serial

card = 0

#criar conexão do wifi com o arduíno
#criar conexão do card com o arduíno
#criar conexão do LED com o arduíno
#criar conexão do LCD com o arduíno

def user():
    while True:
        if card == 1:
            #lED R('H')
            #LCD print('Bem vindo [nome]')
            #Turn bay status to occupied
            pass
        elif card == 0:
            pass
            #LED R('L')
            #LED O('H')
            #LCD print('Baía ocupada')
            #Turn user status to "not in the bay"
    while not True:
         #LED G('H')
         #LCD print('Baía livre para uso')
         pass
        
