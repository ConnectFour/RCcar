
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "00002"; // Define the transmit pipe

RF24 radio(7, 8); // Create a Radio
int joystick[2];  // 2 element array holding Joystick readings

float count = 0;
float ok = 0;
float sig = 0;

void setup()   /**** SETUP: RUNS ONCE ****/
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
 
}//--(end setup )-


void loop()   /**** LOOP: RUNS CONSTANTLY ****/
{
  if ( radio.available() )
  {
    {
      // Fetch the data payload
      radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.println(joystick[0]);
      ok ++;
    }
  }
  else
  {
    Serial.println("No radio available");
  }
  count ++;
  sig = (ok / count) * 100;

  Serial.print("percent of time signal is available ");
  Serial.print(sig);
  Serial.println("%");

delay(1000);
}

//--(end main loop )-


//NONE
//*******( THE END )*********
