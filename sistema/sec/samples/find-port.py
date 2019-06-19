import serial

serial.tools.list_ports.comports():
    if "Arduino" in port[1]:
        portacom = port[0]
        
serial.Serial(portacom, 9600, etc)        

        

