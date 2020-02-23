
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define enA 5
#define in1 6
#define in2 3
#define enB 11
#define in3 9
#define in4 10

const byte address[6] = "00002"; // Define the transmit pipe

RF24 radio(7, 8); // Create a Radio

int motorSpeedA = 0;
int motorSpeedB = 0;
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
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
}//--(end setup )-


void loop()   /**** LOOP: RUNS CONSTANTLY ****/

{
  int xAxis = joystick[0];

  if ( radio.available() )
  {
    {
      // Fetch the data payload
      radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.println(joystick[0]);
      ok ++;
    }
        if (xAxis < 900)
        {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedA = map(xAxis, 900, 650, 0, 255);
    //motorSpeedB = map(xAxis, 470, 0, 0, 255);
        }
    else if (xAxis > 900)
        {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedA = 0; //map(xAxis, 550, 1023, 0, 255);
   // motorSpeedB = 0 //map(xAxis, 550, 1023, 0, 255);
        }
  else{
       motorSpeedA = 0;
       motorSpeedB = 0;
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
 analogWrite(enA, motorSpeedA);
 analogWrite(enB, motorSpeedB);

}

//--(end main loop )-

//*******( THE END )*********
