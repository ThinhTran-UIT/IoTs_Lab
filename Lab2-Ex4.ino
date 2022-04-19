
//*************************************************************
const int pirPin = 8;      //PIR sensor attached to digital pin 8
const int redledPin = 7;   //red LED attached to digital pin 7
const int greenledPin = 6; //green LED attached to digital pin 6
const int buzzerPin = 5;   //active piezo buzzer attached to digital pin 5 
                           //(you can use any PWM pin - 3, 9, 10, (6 in use here already) or 11)
int state = LOW;             // by default, no motion detected
//**************************************************************
void setup()
{
  pinMode(buzzerPin, OUTPUT);    //sets buzzerPin as OUTPUT
  pinMode(pirPin, INPUT);        //sets pirPin as INPUT
  pinMode(redledPin, OUTPUT);    //sets redledPin as OUTPUT
  pinMode(greenledPin, OUTPUT);  //sets greenledPin as OUTPUT
  Serial.begin(9600);            //initialize serial communications at 9600 bps
}

void loop()
{
  int sensorValue = analogRead(A5);//reads the status of PIR sensor
  Serial.println(sensorValue);
  if (sensorValue != 1023) {//checks if sensor active
    digitalWrite(redledPin, HIGH); //red LED is on
    digitalWrite(greenledPin, LOW);//green LED is off
    playTone(300, 160);
    delay(150);                //sets delay for 150 ms 
    if (state == LOW) {
      Serial.print ("Alarm!!! Motion detected");//prints message on Serial Monitor
      state = HIGH;            //update variable state to HIGH
    }
  }
  else {
    digitalWrite(redledPin, LOW);   //red LED is off
    digitalWrite(greenledPin, HIGH);//green LED is on
    playTone(0, 0);
    delay(300);             //sets delay for 300 ms  
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;                //update variable state to LOW
    }
  }
}
//*********************************************************************
void playTone(long duration, int freq) {
    duration *= 1000;// duration in mSecs, frequency in hertz
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(buzzerPin,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(buzzerPin, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
    }