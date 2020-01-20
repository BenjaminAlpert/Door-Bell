#include <Servo.h>

/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
Servo myservo;


const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  radio.write("ring", sizeof("ring"));


  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  myservo.attach(9);
  
}
void loop() {
  if(radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    int val = ((String)text).toInt();
    myservo.write(val);
  }
}
