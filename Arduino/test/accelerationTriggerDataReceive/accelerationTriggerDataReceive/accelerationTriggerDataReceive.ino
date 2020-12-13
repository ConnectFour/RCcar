#include <RF24.h>
#include <SPI.h>
#include <Servo.h>

RF24 myRadio (7, 8);
byte addresses [][6] = {"0"};

// Create servo object to control a servo
Servo servo;  
int pos = 0;

// Joystick Pins
//int steeringPin   = A0;   // Steering Josytick Pin
int steeringValue = 0;    // variable to read the value from the analog steeringPin

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
  
  servo.attach(2); // Attach the servo object to the servo Pin
  
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
      servo.write(data.servoAngle);// set the angle on the Servo
    }
    
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.acceleration);
  Serial.println(data.reverse);
  Serial.println(data.servoAngle);
  
  }
}
