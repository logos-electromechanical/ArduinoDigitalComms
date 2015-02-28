#include <SPI.h>

// pins
#define EEPROM_SEL 10
#define WP         8
#define HOLD       9

// op codes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2 

// other constants
#define BUFLEN 128
#define MAXADDR 65000

void setup() {
  char s;
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  Serial.begin(9600);
  pinMode(EEPROM_SEL, OUTPUT);
  pinMode(WP, OUTPUT);
  pinMode(HOLD, OUTPUT);
  digitalWrite(EEPROM_SEL, HIGH);
  digitalWrite(HOLD, HIGH);
  digitalWrite(WP, HIGH);
  Serial.println("Enter W<address> to write to an address");
  Serial.println("Enter R<address> to read from an address");
  digitalWrite(EEPROM_SEL, LOW);              // start the write operation
  SPI.transfer(WREN);                         // enable the write operation
  SPI.transfer(WRSR);                         // write to the status register
  SPI.transfer(0x81);                         // disable write protection
  digitalWrite(EEPROM_SEL, LOW); 
}

void loop() {
  char c;
  byte s, count;
  char buf[BUFLEN];
  int i = 0, flag = -1;
  uint16_t address;
  
  if (Serial.available()) {
    c = Serial.read(); 
  } else {return;} 
  
  if (c == 'W') {
    address = Serial.parseInt();                // grab the address from the serial input
    if (address > MAXADDR) address = MAXADDR;   // bound the address
    Serial.print("Enter data to write>");       // give us a prompt
    while (!Serial.available());                // wait for the start of the string to write
    count = Serial.readBytesUntil('\0', buf, BUFLEN);   // read in the input string
    digitalWrite(EEPROM_SEL, LOW);              // start the write operation
    SPI.transfer(WREN);                         // enable the write operation
    SPI.transfer(WRSR);                         // write to the status register
    SPI.transfer(0x81);                         // disable write protection
    digitalWrite(EEPROM_SEL, LOW); 
    digitalWrite(EEPROM_SEL, LOW);              // start the write operation
    SPI.transfer(WREN);                         // send the write enable byte
    digitalWrite(EEPROM_SEL, HIGH);             // end the transfer
    delay(1);
    digitalWrite(EEPROM_SEL, LOW);              // start the write operation
    SPI.transfer(WRITE);                        // send the write command
    SPI.transfer((char)(address >> 8));                 // send the high byte of the address
    SPI.transfer((char)(address & 0xff));               // send the low byte of the address
    while ((buf[i] != '\0') && (i < BUFLEN) && (i < count)) {  // transfer all the bytes until the end of the buffer or a terminating null
      SPI.transfer(buf[i]);
      Serial.write(buf[i]);
      i++;
    }
    digitalWrite(EEPROM_SEL, HIGH);             // end the transfer
    Serial.println("");
    Serial.println("Transfer completed, waiting for the end of the write cycle");
    while (flag) {
      digitalWrite(EEPROM_SEL, LOW);  
      SPI.transfer(RDSR);
      s = SPI.transfer(0xff);
      digitalWrite(EEPROM_SEL, HIGH); 
      flag = (s & 1);
      delay(10);
    }
    Serial.println("Write cycle complete.");   
  } else if (c == 'R') {
    address = Serial.parseInt();                // grab the address from the serial input
    if (address > MAXADDR) address = MAXADDR;   // bound the address
    Serial.print("Enter number of bytes to read>"); // give us a prompt
    while (!Serial.available());                // wait for the start of the string to write
    count = Serial.parseInt();                  // get the number of bytes to read
    if (count > BUFLEN) count = BUFLEN;         // bound the number of bytes to get
    digitalWrite(EEPROM_SEL, LOW);              // start the write operation
    SPI.transfer(READ);                         // send the read command
    SPI.transfer((char)(address >> 8));                 // send the high byte of the address
    SPI.transfer((char)(address & 0xff));               // send the low byte of the address
    i = 0;
    while (i < count) {
      Serial.write(SPI.transfer(0x00));
      i++;
    }
    Serial.println("");
    
  }

}
