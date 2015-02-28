#define SER    11
#define SRCLK  13
#define SRCLR  7
#define RCLK   6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SER, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(RCLK, OUTPUT);
  digitalWrite(SER, LOW);
  digitalWrite(SRCLK, LOW);
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
      case 'o':
        digitalWrite(SER, HIGH);
        delay(1);
        digitalWrite(SRCLK, HIGH);
        delay(1);
        digitalWrite(SRCLK, LOW);
        delay(1);
        digitalWrite(SER, LOW);
        break;
      case 'O':
        digitalWrite(SER, HIGH);
        delay(1);
        digitalWrite(SRCLK, HIGH);
        delay(1);
        digitalWrite(SRCLK, LOW);
        delay(1);
        digitalWrite(SER, LOW);
        delay(1);
        digitalWrite(RCLK, HIGH);
        delay(1);
        digitalWrite(RCLK, LOW);
        break;
      case 'z':
        digitalWrite(SER, LOW);
        delay(1);
        digitalWrite(SRCLK, HIGH);
        delay(1);
        digitalWrite(SRCLK, LOW);
        delay(1);
        digitalWrite(SER, LOW);
        break;
      case 'Z':
        digitalWrite(SER, LOW);
        delay(1);
        digitalWrite(SRCLK, HIGH);
        delay(1);
        digitalWrite(SRCLK, LOW);
        delay(1);
        digitalWrite(SER, LOW);
        delay(1);
        digitalWrite(RCLK, HIGH);
        delay(1);
        digitalWrite(RCLK, LOW);
        break;
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
        shiftOut(SER, SRCLK, MSBFIRST, out);
        break;
      case 'D':
        out = Serial.parseInt();
        shiftOut(SER, SRCLK, MSBFIRST, out);
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

