#include <Servo.h>
Servo servo;   
int buzzer = 2;
int led = 7;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
int angle = 270;
void setup() {
  // initialize serial communication @ 9600 baud:
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);  
}
void loop() {
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("* Close Fire *");
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    for(angle = 270; angle > 90; angle -= 1)    // command to move from 0 degrees to 180 degrees 
    {                                  
      servo.write(angle);                 //command to rotate the servo to the specified angle
      delay(20);                       
    } 
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("* Distant Fire *");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    break;
  }
  delay(500);  // delay between reads
}