
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const byte address[6] = "00002"; // Define the transmit pipe

RF24 radio(7, 8); // Create a Radio
int trigger_1 = A0;
int steering = A2;

void setup()   /**** SETUP: RUNS ONCE ****/
{
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
}//--(end setup )-

void loop()   /**** LOOP: RUNS CONSTANTLY ****/
{
  trigger_1 = analogRead(trigger_1);
  radio.write(trigger_1,1);

  steering = analogRead(A2);
  radio.write(steering,0);

//Serial.println(trigger_1);
Serial.println(steering);

}//--(end main loop )-


//NONE
//*******( THE END )*********
