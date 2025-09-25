#include <Arduino.h>

#define LED 2

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034


long duration;
long lastDuration;

unsigned long start;
unsigned long end;

boolean measuring = false;

float distanceCm;
float distanceInch;
float difference;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED, OUTPUT);
}

void startTime() {
  measuring = true;
  digitalWrite(LED, LOW);
  start = millis();
  Serial.println("Start triggered");
}

void endTime() {
  measuring = false;
  digitalWrite(LED, HIGH);
  end = millis();
  difference = end - start;
  Serial.print("Difference (s): ");
  Serial.println(difference/1000);
}

void saveResult() {
  for (int i = 0; i <= 25; i++) {
    digitalWrite(LED, LOW);
    delay(150);
    digitalWrite(LED, HIGH);
    delay(50);
  }
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  if ((lastDuration == NULL or lastDuration > duration*2) and measuring == false) {
    startTime();
  } else if (lastDuration > duration*2 and measuring == true) {
    endTime();
    saveResult();
  }
  lastDuration = duration;
  delay(100);
}