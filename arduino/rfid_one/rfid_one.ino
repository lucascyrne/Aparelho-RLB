#include <SPI.h>
#include <MFRC522.h>


// Pinagens
// uso do #define pois utiliza menos espaço na memoria 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   //instancia

//Pinos do LED RGB
int ledVermelho =2;
int ledVerde =3;
int ledAzul =4;
 
char st[20];

void setup() 
{
  Serial.begin(9600);   // Inicia comunicação Serial
  SPI.begin();          // Inicia comunicação SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522

  //Inicia os pinos do LED RGB como saida
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

}

void loop() 
{

  //Metodo chamado quando a tag é valida e cadastrada
  void tagValida()
  {
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
  }

  //Metodo chamado quando a tag invalida / desconhecida
  void tagInvalida()
  {
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledVermelho,  HIGH);
    digitalWrite(ledVerde, LOW);
  }

   void setColor(int vermelho, int verde, int azul)
  {
    analogWrite(ledVermelho, vermelho);
    analogWrite(ledVerde, verde);
    analogWrite(ledAzul, azul);  
  }

  //Metodo chamado quando cartão é retirado da baía 
  void tagVazia()
  {
    setColor(255,128,0);
  }

  //Metodo chamado quando a baía está livre
  void baiaLivre()
  {
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledVermelho,  LOW);
    digitalWrite(ledVerde, HIGH);
  }

  baiaLivre();
  
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
  
  if (rlb.substring(1) == "44 39 59 52") { // ID cartão 
    Serial.println("Identified card");
    tagValida();
    Serial.println();
    delay(3000);
     
  } else {
    Serial.println("This card is not valid");  
    tagInvalida();
    Serial.println();
    
    delay(3000);
  }
}
