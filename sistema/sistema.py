import serial as ser
import time
import json
from mysql.connector import connection
from mysql.connector import errorcode


#conecxao sql 
cnx = connection.MySQLConnection(user='u185329633_user', password='realob',
                                 host='localhost,
                                 database='u185329633_baia')
cnx = connection.MySQLConnection(user='u185329633_form', password='realob',
                                 host='localhost,
                                 database='u185329633_form')

#BANCO DE DADOS
rlb_db = ''' 
{
    "card_id": [
        {
            "id": "290441FB5",
            "nome": "Lucas Cyrne",
            "baia": "A1",
            "categoria": "Engenheiro de Software",
            "login": "",
            "senha":"",
            "email":"",
            "telefone":""
        }
    ]
}
'''

print('-=' * 40)
print('Banco de dados disponíveis: ')
print()
data = json.loads(rlb_db)
print(data)
print('-=' * 40)

ser = ser.Serial('COM13', baudrate = 9600, timeout = 1)

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
data = []
dado = []
card_id = 0
btn_data = open('btn_data.txt', 'a+')
cid_data = open('cid_data.txt', 'a+')  

while True:
    rdm()
    keyboard()
    dado = getValues().split(',')
    if dado != '':

        #INICIA PROCEDIMENTO
        rdm()
        if cid == True:
            ser.write('n')




        resp = str(input('Deseja continuar? (s/n)'))
        if resp in 'Ss':
            print('Sistema continua.')
        else:
            break
       
 

     

cid_data.close()