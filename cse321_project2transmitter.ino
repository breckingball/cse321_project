#include <SPI.h>
#include "RF24.h"

#define JOYSTICK1_X A0
#define JOYSTICK2_X A1
RF24 radio(9, 10);  // CE, CSN pins

// address for radio communication, same as receiver
const byte address[6] = "00001"; 

void setup() {
  if(!radio.begin()){
    Serial.println("failed");
  }
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  uint16_t joys[2] = {map(analogRead(JOYSTICK2_X),0,1023,0,510),map(analogRead(JOYSTICK1_X),0,1023,0,510)};
  radio.write(&joys, sizeof(joys));
}
