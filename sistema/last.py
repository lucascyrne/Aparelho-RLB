import serial

def getValues():
    
    s.write(b'g')
    arduinoData = ser.readline().decode('UTF-8').split('\r\n')
    print(arduinoData)

getValues()


while True:     

    s = serial.Serial('COM21', 9600)
    time.sleep(2)
    s.write(b'Passe o cartao')
    s.write(b'\n Escolha a baia')    