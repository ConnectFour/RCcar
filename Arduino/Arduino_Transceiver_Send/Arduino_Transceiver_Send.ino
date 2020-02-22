
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

const byte address[6] = "00002"; // Define the transmit pipe

RF24 radio(7, 8); // Create a Radio
int joystick[2];  // 2 element array holding Joystick readings

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
  joystick[0] = analogRead(JOYSTICK_X);
  joystick[1] = analogRead(JOYSTICK_Y);
  
  radio.write( joystick, sizeof(joystick) );
Serial.println(joystick[0]);
}//--(end main loop )-


//NONE
//*******( THE END )*********
