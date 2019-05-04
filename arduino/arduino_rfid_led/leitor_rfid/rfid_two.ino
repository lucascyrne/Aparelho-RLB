char rfid_token[13];    // buffer to store the received data from serial  
char rfid_ref_token[13]="6C00908D3B4A";  // reference token   

void setup()
{
  Serial.begin(9600);  // initializing the serial communication  
}

void loop()
{
  if(Serial.available() > 0)  // checking if card is punched or not
  {
    Serial.readBytesUntil('\0',rfid_token,12);  // storing the serial data on buffer
    if(!(strcmp(rfid_ref_token,rfid_token)))  // comparing two string
    {
      Serial.println("entered card is correct");  //printing statement on serial port
    }
    else
    {
     Serial.println("please enter correct card");
    }
  }
}
