#include "SoftwareSerial.h"
#include <Keypad.h>
#include <RDM6300.h>

// RFID

//Inicializa a serial nos pinos 2 (RX) e 3 (TX)
SoftwareSerial RFID(2, 3);

uint8_t Payload[6]; // used for read comparisons

RDM6300 RDM6300(Payload);

// KEYPAD

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3','A'},
  {'4', '5', '6','B'},
  {'7', '8', '9','C'},
  {'*', '0', '#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 11, 12};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup() {

  Serial.begin(9600);
  RFID.begin(9600);

}

void loop() {

  //KEYPAD

  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
  }

  // RFID
    //Aguarda a aproximacao da tag RFID
  while (RFID.available() > 0) {
    uint8_t c = RFID.read();
    if (RDM6300.decode(c))    {
      Serial.print("ID TAG: ");
      Serial.println();
      //Mostra os dados no serial monitor
      for (int i = 0; i < 5; i++)      {
        Serial.print(Payload[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      delay(1000);
    }
  }


}
