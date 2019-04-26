#include <SPI.h>
#include <MFRC522.h>


// Pinagens
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   //instancia
 
char st[20];

void setup() 
{
  Serial.begin(9600);   // Inicia comunicação Serial em 9600 baud rate
  SPI.begin();          // Inicia comunicação SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}
void loop() 
{
  // Verifica exixtencia de novos cartoes
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Lê o cartao
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  // Mostra UID na serial
  Serial.print("UID da tag :");
  String jorge= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     jorge.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     jorge.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  jorge.toUpperCase();
  
  if (jorge.substring(1) == "44 39 59 52") //cartao
  {
    Serial.println("Cartão Identificado");
    Serial.println();
    delay(3000);
     
  }
 
  if (jorge.substring(1) == "14 2C F7 E9") //Chaveiro
  {
    Serial.println("Chaveiro Identificado");
    Serial.println();
    delay(3000);
    }
else {
  Serial.println("esse cartão não é valido");  
}
}
 
 
