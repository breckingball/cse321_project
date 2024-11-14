#include <SPI.h>
#include "RF24.h"

// RF24 radio communication library
RF24 radio(9, 10);  // CE, CSN pins

// Pin numbers
#define HEADLIGHTS 2
#define FRONT_PIN 3
#define BACK_PIN 4

#define INPUT_1 7
#define INPUT_2 8
#define INPUT_3 14
#define INPUT_4 15

#define EN12 5
#define EN34 6

#define PHOTO A7

// How dark must it be to activate lights
#define DARK_THRESHOLD 200

// How close must an obstacle be to activate brakes
#define DISTANCE_THRESHOLD 50

const byte address[6] = "00001";  // Address for communication

int getFrontDistance(), getBackDistance();

void setup() {
  Serial.begin(9600);
  pinMode(HEADLIGHTS,OUTPUT);
  pinMode(INPUT_1,OUTPUT);
  pinMode(INPUT_2,OUTPUT);
  pinMode(INPUT_3,OUTPUT);
  pinMode(INPUT_4,OUTPUT);
  pinMode(EN12,OUTPUT);
  pinMode(EN34,OUTPUT);
  
  // If radio initizalization does not work, print message
  if(!radio.begin())
    Serial.println("failed");

  radio.openReadingPipe(1, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  int left_joy, right_joy;

  // Reading the radio transmission if available
  if (radio.available()) {
    uint16_t joys[2];
    radio.read(&joys, sizeof(joys));
    left_joy = joys[0];
    right_joy = joys[1];
  }

  // Calculating if the car can move forward or backward
  // max = 510 if there is no obstacle or 255 if there is
  // min = 0 if there is no obstacle or 255 if there is
  int max = 255 + 255 * getFrontDistance();
  int min = 255 - 255 * getBackDistance();

  // Writing the values to the motor enable pins
  // Sets the speed to 0 if the joystick is somewhere that the 
  // sensors don't allow it
  analogWrite(EN12, (left_joy<=max && left_joy>=min) ? abs(left_joy-255) : 0);
  analogWrite(EN34, (right_joy<=max && right_joy>=min) ? abs(right_joy-255) : 0);

  // Writing to inputs of the motor driver
  int left_direction = left_joy < 255;
  int right_direction = right_joy < 255;
  digitalWrite(INPUT_1, left_direction);
  digitalWrite(INPUT_2, !left_direction);
  digitalWrite(INPUT_3, right_direction);
  digitalWrite(INPUT_4, !right_direction);

  // Reading the light value from the photoresistor
  int light = analogRead(PHOTO);
  light < 200 ? digitalWrite(HEADLIGHTS, HIGH) : digitalWrite(HEADLIGHTS, LOW);
}

// Function that returns true if there is no obstacle in front and false if there is
// Uses ultrasonic sensors
// Send ping, see how long it takes to receive it back,
// calculate the distance using the speed of sound
int getFrontDistance(){
  pinMode(FRONT_PIN, OUTPUT);
  digitalWrite(FRONT_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(FRONT_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRONT_PIN, LOW);

  pinMode(FRONT_PIN, INPUT);
  int time = pulseIn(FRONT_PIN, HIGH);
  int distance = time * 0.034 / 2;

  return !(distance <= DISTANCE_THRESHOLD);
}

// Function that returns true if there is no obstacle in back and false if there is
// Uses ultrasonic sensors
// Send ping, see how long it takes to receive it back,
// calculate the distance using the speed of sound
int getBackDistance(){
  pinMode(BACK_PIN, OUTPUT);
  digitalWrite(BACK_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(BACK_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(BACK_PIN, LOW);

  pinMode(BACK_PIN, INPUT);
  int time = pulseIn(BACK_PIN, HIGH);
  int distance = time * 0.034 / 2;

  return !(distance <= DISTANCE_THRESHOLD);
}