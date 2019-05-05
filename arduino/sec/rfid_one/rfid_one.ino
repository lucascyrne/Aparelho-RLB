#include <SPI.h>
#include <MFRC522.h>


// Pinagens
// uso do #define pois utiliza menos espaço na memoria 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   //instancia
 
char st[20];

void setup() 
{
  Serial.begin(9600);   // Inicia comunicação Serial
  SPI.begin();          // Inicia comunicação SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
}

void loop() 
{
  // Verifica existência de novos cartoes
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Lê o cartao
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Printa o ID do cartão na serial
  Serial.print("CARD ID:");
  String rlb = "";
  byte letra;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     rlb.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     rlb.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message:");
  rlb.toUpperCase();
  
  if (rlb.substring(1) == "44 39 59 52") // ID cartão {
    Serial.println("Identified card");
    Serial.println();
    delay(3000);
     
} else {
  Serial.println("This card is not valid");  
  Serial.println();
  delay(3000);
}
}
 
 
