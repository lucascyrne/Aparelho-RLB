//Aparelho RLB (Versão Alfa) - Controle de Acesso com leitor RFID 

//Biblioteca do protocolo SPI 
#include <SPI.h>
//Biblioteca do RFID
#include <MFRC522.h>

//Pinos de definição 
#define SS_PIN 10
#define RST_PIN 9
//Cria a instacia do RFID (mfrc522)
MFRC522 mfrc522(SS_PIN, RST_PIN);   

//Aqui colocamos as Tags que desejamos autorizar
String tagsCadastrada[2] ={"44 39 59 52","14 2C F7 E9"}; // ATENÇÃO: EDITAR POSTERIORMENTE!!!

 //Pinos do LED RGB
 int ledVermelho =2;
 int ledVerde =3;
 int ledAzul =4;
 
void setup() 
{
  // Inicia a serial
  Serial.begin(9600);
  //inicia a conexão SPI
  SPI.begin();  
  // Inicia MFRC522  
  mfrc522.PCD_Init();  
  Serial.println();
  
  //Inicia os pinos do LED RGB como saida
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

}
 
void loop() 
{

  String conteudo;

  //Metodo inicial
  mensageminicial();
   
  Serial.println();
  //booleana que valida a tag lida
  //como autorizada ou não
  boolean tagVerificada = false;  
  
  Serial.print("Leitura : ");
    
  //verifica se a tag lida coincide com uma das tags 
  //cadastada no array
 for(int indice = 0; indice < sizeof(tagsCadastrada); indice++){
  //if (conteudo.substring(1) == "24 B4 8B 19") //UID 1 
   if (conteudo.substring(1) == tagsCadastrada[0]) //UID 1
  {
   //Se sim imprime na Serial
    Serial.println("Olá, Carlos!");
    Serial.println("Acesso Liberado!");
    
    //tag encontrada
    tagVerificada = true;
    //este metodo acende o led azul (autorizado)
    tagValida();
    delay(4000);
    leitorRfid();
    if(conteudo == "") {
      tagVazia();
      delay(6000);
      mensageminicial();
    } 
    delay(6000);
    
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo = "";    
  }
  
  //if (conteudo.substring(1) == "55 FC F9 0D") //UID 1
  
  //verifica se a tag lida coincide com uma das tags 
  //cadastada no array
  if (conteudo.substring(1) == tagsCadastrada[1]) //UID 1
  {
    //Se sim imprime na Serial
    Serial.println("Olá, Janaína!");
    Serial.println("Acesso Liberado!");
       
    //tag encontrada
    tagVerificada = true;
    //este metodo acende o led azul (autorizado) 
    tagValida();
    delay(4000);
    leitorRfid();
    if(conteudo == "") {
      tagVazia();
      delay(6000);
      mensageminicial();
    }
    delay(6000);
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo= "";
  }
  
  //caso o conteudo não seja "" e a tag Verficada
  //esteja falsa.
  //Informa o usuario que não tem acesso
  if((tagVerificada == false)&&((conteudo) != ""))   {
    
    //Se ambas condições forem verdadeira 
    //imprime na Serial uma mensagem de negação ao usuario
    Serial.println("Usuario Desconhecido!");
    Serial.println("Acesso Negado!!");
    
    //este metodo acende o led vermelho (não autorizado)
    tagInvalida();
    delay(10000);  
    //Incia o processo novamente
    mensageminicial();
    //limpa a String conteudo para fazer nova leitura
    conteudo= "";
  }
}
  
} 

//Metodo Inicial que informa ao usuario o que deve ser feito  
void mensageminicial()
{
  
  conteudo = leitorRfid(); // lê e armazena o UID do cartão na variável "conteudo"
  
  while (False) {
  Serial.println();
  Serial.println("Aproxime o seu cartao de leitor");

  digitalWrite(ledAzul,LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, HIGH);
  
  Serial.println();
  }
}

String leitorRfid()
{
  //Aguarda proximidade do cartão / tag
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
   //Seleciona o cartão / tag
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  //String que armazenará o UID do cartão
  String conteudo = "";
  //variavel que coletará os bytes lidos
  byte letra;
  //coloca o valor da variavel conteudo toda em Maisculo
  conteudo.toUpperCase();
  
  //dentro deste FOR, armazena byte a byte e 
  //concatena na variavel conteudo
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  return conteudo;
}

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


//Metodo chamado quando cartão é retirado da baía 
void tagVazia()
{
  setColor(255,128,0);
}

void setColor(int vermelho, int verde, int azul)
{
  analogWrite(ledVermelho, vermelho);
  analogWrite(ledVerde, verde);
  analogWrite(ledAzul, azul);  
}
