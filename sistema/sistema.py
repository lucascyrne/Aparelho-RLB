import serial as ser
import time
import json
from mysql.connector import connection
from mysql.connector import errorcode


#BANCO DE DADOS MYSQL
cnx = connection.MySQLConnection(user='u185329633_user', password='realob',
                                 host='localhost,
                                 database='u185329633_baia')
cnx = connection.MySQLConnection(user='u185329633_form', password='realob',
                                 host='localhost,
                                 database='u185329633_form')


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

#VARS
dado = []
btn_data = open('btn_data.txt', 'a+')
cid_data = open('cid_data.txt', 'a+')  
ser = ser.Serial('COM13', baudrate = 9600, timeout = 1)
time.sleep(1)

while True:
    
       