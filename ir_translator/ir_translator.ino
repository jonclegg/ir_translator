#include "IRLibAll.h"

IRrecvPCI myReceiver(2); //create receiver and pass pin number
IRdecode myDecoder;   //create decoder
IRsend mySender;  // Uses pin 9

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it

    //myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    //Serial.println(" ");
    //Serial.print("Code: ");
    //Serial.println(myDecoder.value); //prints the value a a button press
    //Serial.println(" ");

    switch (myDecoder.value)
    {
    case 0x20DFC03F:
      Serial.println("volume down");
      mySender.send(NEC, 0x5EA1D827); //Amp vol up              
      mySender.send(NEC, 0x5EA1D827); //Amp vol up              
      break;
    case 0x20DF40BF:
      Serial.println("volume up");
      mySender.send(NEC, 0x5EA158A7); //Amp vol down
      mySender.send(NEC, 0x5EA158A7); //Amp vol down
      break;
    }
    
    myReceiver.enableIRIn();      //Restart receiver
  }
}

/*
void loop() 
{
  if (myReceiver.getResults()) 
  {
    if (myDecoder.decode()) 
    {
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(myDecoder.value); //prints the value a a button press
    Serial.println(" ");
      
      switch (myDecoder.value)
      {
      case 0x20DF40BF:
        Serial.println("volume up");
        mySender.send(NEC, 0x5EA1D827); //Amp vol up        
        break;
      case 0x20DFC03F:
        Serial.println("volume down");
        mySender.send(NEC, 0x5EA158A7); //Amp vol down
        break;
      }
       
      delay(200);
      myReceiver.enableIRIn(); //Re-enable rcvr after sending
      digitalWrite(LED_BUILTIN, LOW); 
    }
  }
}

*/
