g#include <RF24.h>
#include <SPI.h>


RF24 myRadio (7, 8);
byte addresses [][6] = {"0"};

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


void setup() {
  Serial.begin(9600);
  delay(1000);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);

}

void loop() {

  data.steer = analogRead(A0);
  data.acceleration = analogRead(A2);
  data.reverse = analogRead(A4);
  int angleLimit = 45; // Angle to limit the servo
  data.servoAngle = map(data.steer, 0, 1023, 0+angleLimit, 180-angleLimit);

  if(data.steer < 500);
  {
    data.steer =  512;
  }
  
  myRadio.write(&data, sizeof(data));

  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.servoAngle);
  Serial.println(data.acceleration);
  Serial.println(data.reverse);
  data.id = data.id + 1;
  data.acceleration = data.acceleration+0.1;
  delay(100);
}
