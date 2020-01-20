#include <SPI.h>

/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

* Modified by Benjamin Alpert as part of a Door-Bell Project
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int enterButton = 4;
int doNotEnterButton = 5;

void setup() {
  //Serial.begin(9600);

  pinMode(enterButton, INPUT);
  pinMode(doNotEnterButton, INPUT);
  
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    if(text == "ring"){
      tone(3, 50);
      //delay(1000);
    }
  }
  else{
    noTone(3);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

bool enterButtonPressed = false;
bool doNotEnterButtonPressed = false;

void loop() {
  delay(1);
  if(digitalRead(enterButton)){
    enterButtonPressed = true;
    doNotEnterButtonPressed = false;
  }
  if(digitalRead(doNotEnterButton)){
    doNotEnterButtonPressed = true;
    enterButtonPressed = false;
  }

  
  if(enterButtonPressed){ //enter button is pressed
    radio.write("0", sizeof("0"));
    noTone(3);
  }
  else if(doNotEnterButtonPressed){ //do not enter button is pressed
    radio.write("180", sizeof("180"));
    noTone(3);
  }
  else{ //no button is pressed
    radio.write("90", sizeof("90"));
  }
}
