import serial
import time

ser = serial.Serial('COM13', baudrate = 9600, timeout = 1)

#VARS
data = []
dado = []
card_id = 0
btn_data = open('btn_data.txt', 'a+')
cid_data = open('cid_data.txt', 'a+')

#BAIAS
baias = "b1", "b2", "b3", "b4", "b5"
print(baias)

#USERS
users = "Lucas Cyrne", "Bennyson Brecht", "Pedro Vilella"
users_list = ["","","","",""]


print(users)

def getValues():
    
    ser.write(b'g')
    arduinoData = ser.readline().decode('UTF-8').split('\r\n')

    return arduinoData[0]

def keyboard():
    #KEYBOARD CODE
    if dado[0] == "k":
        print('numberpad identificado')
        btn = dado[1]
        print(btn)

def rdm():
    #RDM CODE    
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

while True:

    dado = getValues().split(',')
    if dado != '':

    #INICIA PROCEDIMENTO
    print('Passe o cartão ou insira o nº da baia: ')





    

    resp = str(input('Deseja continuar? (s/n)'))
    if resp in 'Ss':
        print('Sistema continua.')
    else:
        break


     

cid_data.close()