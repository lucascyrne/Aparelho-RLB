#include <RDM6300.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

// RFID
const int BUFFER_SIZE = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const int DATA_SIZE = 10; // 10byte data (2byte version + 8byte tag)
const int DATA_VERSION_SIZE = 2; // 2byte version (actual meaning of these two bytes may vary)
const int DATA_TAG_SIZE = 8; // 8byte tag
const int CHECKSUM_SIZE = 2; // 2byte checksum

SoftwareSerial ssrfid = SoftwareSerial(6, 8);

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame
int buffer_index = 0;

// KEYBOARD

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {

  Serial.println("INIT DONE");

  RFID.begin(9600);   //Inicializa a serial para comunicacao com o PC
  Serial.begin(9600);   //Informacoes iniciais
  Serial.println("Leitor RFID RDM6300\n");

}

void loop() {

  //RFID

  //Inicializa a serial nos pinos 2 (RX) e 3 (TX)
  SoftwareSerial RFID(10, 12);

  uint8_t Payload[6]; // used for read comparisons

  RDM6300 RDM6300(Payload);

  void setup()
  {
    
  }

  void loop() {
    if (RFID.read() != 0 ) {
      //Aguarda a aproximacao da tag RFID
      while (RFID.available() > 0) {
        uint8_t c = RFID.read();
        if (RDM6300.decode(c))    {
          Serial.print("ID TAG: ");
          //Mostra os dados no serial monitor
          for (int i = 0; i < 5; i++)      {
            Serial.print(Payload[i], HEX);
            Serial.print(" ");
          }
        }
      }
    } else {
      Serial.println("Aproxime");
      delay(5000);
    }

  }
}

  // KEYBOARD

  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
  }
}


