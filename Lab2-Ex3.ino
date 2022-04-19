// 18520771
// Dinh Thi My Hoan
// Lab1 - Ex2
#define DEBUG 0

int first = 8;
int second = 9;
int third = 10;
int fourth = 11;
int fifth = 12;
int sixth = 13;
int button = 4;
int pressed = 0;

void setup() {
  for (int i=first; i<=sixth; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(button, INPUT);
  randomSeed(analogRead(0));
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

}

void buildUpTension() {
  for (int i=first; i<=sixth; i++) {
    if (i!=first) {
      digitalWrite(i-1, LOW);
    }
    digitalWrite(i, HIGH);
    delay(100);
  }
  for (int i=sixth; i>=first; i--) {
    if (i!=sixth) {
      digitalWrite(i+1, LOW);
    }
    digitalWrite(i, HIGH);
    delay(100);
  }
}

void showNumber(int number) {
  digitalWrite(first, HIGH);
  if (number >= 2) {
    digitalWrite(second, HIGH);
  }
  if (number >= 3) {
    digitalWrite(third, HIGH);    
  }
  if (number >= 4) {
    digitalWrite(fourth, HIGH);    
  }
  if (number >= 5) {
    digitalWrite(fifth, HIGH);    
  }
  if (number == 6) {
    digitalWrite(sixth, HIGH);    
  }
}

int throwDice() {
  int randNumber = random(1,7);
  #ifdef DEBUG
    Serial.println(randNumber);
  #endif
  return randNumber;
}

void setAllLEDs(int value) {
  for (int i=first; i<=sixth; i++) {
    digitalWrite(i, value);
  }
}

void loop() {
  pressed = digitalRead(button);
  if (pressed == HIGH) {
    setAllLEDs(LOW);
    buildUpTension();
    int thrownNumber = throwDice();
    showNumber(thrownNumber);
  } 
}