#include <Wire.h>
#include <SPI.h>

// pins
#define SER    11
#define SRCLK  13
#define SRCLR  7
#define RCLK   6
#define INT    4

// I2C address
#define ADDR   0x20

// addresses
#define INPUTS_LOW        0x00
#define INPUTS_HI         0x01
#define CONF_LOW          0x06 
#define CONF_HI           0x07


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  Wire.begin();
  pinMode(SRCLR, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(INT, INPUT);
  digitalWrite(SRCLR, HIGH);
  digitalWrite(RCLK, LOW);
  digitalWrite(INT, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t out;
  char c;
  
  if (Serial.available()) {    // this section writes something to the shift register so we have something to read
    c = Serial.read();
    if (c = 'w') {
        out = Serial.parseInt();
        SPI.transfer(out);
        delay(1);
        digitalWrite(RCLK, HIGH);
        delay(1);
        digitalWrite(RCLK, LOW);
    }
  }
  
  if (digitalRead(INT) == LOW) {         // check for interrupt line
    Serial.println("Interrupt Fired!");
    Wire.beginTransmission(ADDR);        // start the I2C transmission
    Wire.write(INPUTS_LOW);              // send the address to read from
    Wire.endTransmission(false);         // execute the transmission with a repeated start
    Wire.requestFrom(ADDR, 2);                 // grab two bytes
    Serial.print("Reading Inputs: ");
    while(Wire.available()) {
      Serial.print(Wire.read(), HEX);
      Serial.print(" ");
    }
    Serial.println("");
  
  }
  
}

