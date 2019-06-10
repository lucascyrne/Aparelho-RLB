import serial
import time

ser = serial.Serial('COM3', baudrate = 9600, timeout = 1)
time.sleep(2)
numPoints = 10
dataList = [0]*numPoints
dataFile = open('dataFile.txt', 'w')


def getValues():

    ser.write(b'g')
    arduinoData = ser.readline().decode('UTF-8').split('\r\n')

    return arduinoData[0]

def handleValues():

    # while(1):
    while(ser.isOpen()):

        for i in range(0,  numPoints):
            data = getValues()
            dataFile.write(data + ' ')
            dataList[i] = data
            data.strip()

        print(dataList)

        break 

def read_sensor():

    print('Inicialize com seu cartão.')
    handleValues()

    if 'ID' in dataList:
        pos = dataList.index('ID')
        card_id = pos + 1
    
    print(f'ID: {card_id}')



read_sensor()
dataFile.close()






""" # while(1):
while(ser.isOpen()):

    userInput = input('Get data points? (type "e") \n')

    if userInput == 'e':
        for i in range(0, numPoints):
            data = getValues()
            dataFile.write(data + ' ')
            dataList[i] = data

        print(dataList)

        dataFile.close()
        break """

