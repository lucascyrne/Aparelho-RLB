#include <SPI.h>
#include <MFRC522.h>


// Pinagens
// uso do #define pois utiliza menos espaço na memoria 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   //instancia

//Pinos do LED RGB
int ledVermelho =3;
int ledVerde =5;
int ledAzul =6;
 
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

  bool verificarCartao()
  {
    // Verifica existência de novos cartoes
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return true;
    } else {
      return false;
    }
  }
  
  //Metodo chamado quando a tag é valida e cadastrada
  void tagValida()
  {
    Serial.println("led azul");
    digitalWrite(ledAzul,HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
  }

  //Metodo chamado quando a tag invalida / desconhecida
  void tagInvalida()
  {
    Serial.print("led vermelho");
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledVermelho,  HIGH);
    digitalWrite(ledVerde, LOW);
    delay(2000);
  }

  //Metodo chamado quando cartão é retirado da baía 
  void tagVazia()
  {
    Serial.println("LED LARANJA");
    analogWrite(ledVermelho, 255);
    analogWrite(ledVerde, 128);
    analogWrite(ledAzul, 0);
  }

  //Metodo chamado quando a baía está livre
  void baiaLivre()
  {
    digitalWrite(ledAzul,LOW);
    digitalWrite(ledVermelho,  LOW);
    digitalWrite(ledVerde, HIGH);
  }

void loop() 
{
  
  baiaLivre();
  
  verificarCartao();
  
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
  
  while (rlb.substring(1) == "44 39 59 52") { // ID cartão 
    Serial.println("Cartão Identificado");
    Serial.println("Seja bem vindo, Carlos Sampaio!");
    Serial.println("Acesso Liberado");
    tagValida();
    Serial.println();
    if (rlb.substring(1) != "44 39 59 52") {
      Serial.println("Usuário desconectado");  
      Serial.println();
      tagVazia();
    }    
  }

  while (rlb.substring(1) == "14 2C F7 E9") { // ID cartão 
    Serial.println("Cartão Identificado");
    Serial.println("Seja bem vindo, Ferraz!");
    Serial.println("Acesso Liberado");
    tagValida();
    Serial.println();
    if (rlb.substring(1) != "14 2C F7 E9") {
      Serial.println("Usuário desconectado");  
      Serial.println();
      tagVazia();
    }    
  }

}
