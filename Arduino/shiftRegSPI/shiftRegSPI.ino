#include <SPI.h>

#define SER    11
#define SRCLK  13
#define SRCLR  7
#define RCLK   6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  pinMode(SRCLR, OUTPUT);
  pinMode(RCLK, OUTPUT);
  digitalWrite(SRCLR, HIGH);
  digitalWrite(RCLK, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t out;
  char c;
  if (Serial.available()) {
    c = Serial.read();
    switch (c) {
      case 'r':
        digitalWrite(RCLK, HIGH);
        delay(1);
        digitalWrite(RCLK, LOW);
        break;
      case 'c':
        digitalWrite(SRCLR, HIGH);
        delay(1);
        digitalWrite(SRCLR, LOW);
        break;
      case 'd':
        out = Serial.parseInt();
        SPI.transfer(out);
        break;
      case 'D':
        out = Serial.parseInt();
        SPI.transfer(out);
        delay(1);
        digitalWrite(RCLK, HIGH);
        delay(1);
        digitalWrite(RCLK, LOW);
        break;
      default:
        Serial.println("Invalid character");
    }
  }
}

