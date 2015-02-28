#include <Wire.h>

// pins
#define INT    4

// I2C address
#define ADDR   0x20

// addresses
#define PORTCONF      0x06 
#define BLINK0        0x02
#define BLINK1        0x0a
#define MAINCONF      0x0f
#define MASTER        0x0e


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t out;
  char c;
  
  if (Serial.available()) {    // this section writes something to the shift register so we have something to read
    c = Serial.read();
    if (c = 'w') {
        out = Serial.parseInt();
        Wire.beginTransmission(ADDR);        // start the I2C transmission
        Wire.write(BLINK0);
        Wire.write(out >> 8);
        Wire.write(out & 0xff);
        Wire.endTransmission();
    }
  }
}

