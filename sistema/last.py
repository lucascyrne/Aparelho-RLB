import serial

def getValues():
    
    s.write(b'g')
    arduinoData = ser.readline().decode('UTF-8').split('\r\n')
    print(arduinoData)

getValues()