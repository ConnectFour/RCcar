#include <SPI.h>

int acceleration = A2;

void setup() {
  Serial.begin(9600);


}

void loop() {

acceleration = analogRead(A2);  
  Serial.println(acceleration);
}
