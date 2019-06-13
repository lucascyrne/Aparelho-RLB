#include "SoftwareSerial.h"
#include <Keypad.h>
#include <RDM6300.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x38,16,2);
String vetor [10];

// RFID

//Inicializa a serial nos pinos 2 (RX) e 3 (TX)
SoftwareSerial RFID(2, 3);

uint8_t Payload[6]; // used for read comparisons

RDM6300 RDM6300(Payload);

// KEYPAD

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 11, 12};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup() {

  Serial.begin(9600);
  RFID.begin(9600);
  lcd.begin (16, 2);

}

void loop() {

  //LCD

  lcd.setCursor(0, 0);
  lcd.print("cade as ferias?");
  lcd.setCursor(0, 1);
  lcd.print("      :/     ");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("");
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(500);

  if (Serial.available() == "n") {
    delay(100);
    char user = Serial.read();
    Serial.print("I received: ");
    lcd.write(user);
    
  }

  // RFID
  //Aguarda a aproximacao da tag RFID
  while (RFID.available() > 0) {
    uint8_t c = RFID.read();
    if (RDM6300.decode(c))    {
      //Mostra os dados no serial monitor
      Serial.print("r,");
      for (int i = 0; i < 5; i++)      {
        Serial.print(Payload[i], HEX);
      }
      Serial.println();
      delay(1000);
    }
  }

  //KEYPAD

  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print("k,");
    Serial.println(customKey);
  }

  

  




  //
  //  vetor[0] = "teste 0";
  //  vetor[1] = "agora 1";
  //  int x = 0;
  //  lcd.setCursor(0,0);
  //  lcd.print("!!!!**!!!!");
  //  lcd.setCursor(5,1);
  //  lcd.print("ROLOU");
  //  while (x <= 2){
  //    delay(2000);
  //    lcd.setCursor(0,0);
  //    lcd.print(vetor[x]);
  //    x++;
  //  }
  //  lcd.backlight();
  //  lcd.setCursor(5,2);
  //  lcd.print("DE SILICIO");
  //  lcd.setCursor(0,3);
  //  lcd.print("********");
  //






}
