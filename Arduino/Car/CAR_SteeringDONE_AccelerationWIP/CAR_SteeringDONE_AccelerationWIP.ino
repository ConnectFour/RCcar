#include <RF24.h>
#include <SPI.h>
#include <Servo.h>

RF24 myRadio (7, 8);
byte addresses [][6] = {"0"};

// Create servo object to control a servo
Servo servo;  
int pos = 0;

//motor
int in1 = 2;
int in2 = 4;
int enA = 3;

int in3 = 5;
int in4 = 10;
int enB = 6;

//data package receive
struct package
{
  int id=1;
  int steer = A0;
  int acceleration = A2;
  int reverse = A4;
  int servoAngle;
};

typedef struct package Package;
Package data;


void setup() 
{
  Serial.begin(9600);
  delay(1000);
  
  // Attach the servo object to the servo Pin
  servo.attach(A2); 

  //motor setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  myRadio.openReadingPipe(1,  addresses[0]);
  myRadio.startListening();

}

void loop() 
{
  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) ); 

      // set the angle on the Servo
      servo.write(data.servoAngle);

      // set motor speed and direction
      if ( data.acceleration <= 500 )
        {
        digitalWrite(in1, HIGH);
        }
        else
          {
          digitalWrite(in1, LOW);
          }
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(enA, 10);
      digitalWrite(enB, 10);
    }
    
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.acceleration);
  Serial.println(data.reverse);
  Serial.println(data.servoAngle);
  
  }
}
