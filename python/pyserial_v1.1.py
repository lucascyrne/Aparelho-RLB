import serial
import time

ser = serial.Serial('COM13', baudrate = 9600, timeout = 1)

data = []
dado = []
card_id = 0
btn_data = open('btn_data.txt', 'a+')
cid_data = open('cid_data.txt', 'a+')

def getValues():
    
    ser.write(b'g')
    arduinoData = ser.readline().decode('UTF-8').split('\r\n')

    return arduinoData[0]

while True:

    dado = getValues().split(',')
    if dado != '':

        if dado[0] == "k":
            print('numberpad identificado')
            btn = dado[1]
            print(btn)
            
        if dado[0]  == "r":
            print('rfid identificado')
            cid = dado[1]
            id= []
            id.append(cid)
            id.append("\n")
            cid_data.writelines(id)
            cid_data.close()
            print(cid)
            print("Sua Baia foi registrada")
            break

cid_data.close()
