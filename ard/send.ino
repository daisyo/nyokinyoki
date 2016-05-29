#include <XBee.h>
uint8_t data[9];

XBee xbee = XBee();
XBeeAddress64 address = XBeeAddress64(0x0013a200, 0x40e74524);
ZBTxRequest zbtx = ZBTxRequest(address, data, sizeof(data));

uint8_t a;
int flag = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  xbee.setSerial(Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    a = Serial.read();
    if (a == 0x7E) { flag = 1; }
    if (flag == 1) {
      if (a != 0x7E) { data[i] = ucharToInt(a); ++i; }
      if (i >= 9) {
        i = 0;
        xbee.send(zbtx);
        flag = 0;
      }
    }
  }
}

uint8_t ucharToInt(unsigned char r) {
  switch (r) {
    case '0': return 0x30;
    case '1': return 0x31;
    case '2': return 0x32;
    case '3': return 0x33;
    case '4': return 0x34;
    case '5': return 0x35;
    case '6': return 0x36;
    case '7': return 0x37;
    case '8': return 0x38;
    case '9': return 0x39;
    case 'A': return 0x41;
    case 'B': return 0x42;
    case 'C': return 0x43;
    case 'D': return 0x44;
    case 'E': return 0x45;
    case 'F': return 0x46;
    case 'G': return 0x47;
    case 'H': return 0x48;
    case 'I': return 0x49;
    case 'J': return 0x4a;
    case 'K': return 0x4b;
    case 'L': return 0x4c;
    case 'M': return 0x4d;
    case 'N': return 0x4e;
    case 'O': return 0x4f;
    case 'P': return 0x50;
    case 'Q': return 0x51;
    case 'R': return 0x52;
    case 'S': return 0x53;
    case 'T': return 0x54;
    case 'U': return 0x55;
    case 'V': return 0x56;
    case 'W': return 0x57;
    case 'X': return 0x58;
    case 'Y': return 0x59;
    case 'Z': return 0x5a;
    case 'a': return 0x61;
    case 'b': return 0x62;
    case 'c': return 0x63;
    case 'd': return 0x64;
    case 'e': return 0x65;
    case 'f': return 0x66;
    case 'g': return 0x67;
    case 'h': return 0x68;
    case 'i': return 0x69;
    case 'j': return 0x6a;
    case 'k': return 0x6b;
    case 'l': return 0x6c;
    case 'm': return 0x6d;
    case 'n': return 0x6e;
    case 'o': return 0x6f;
    default: return 0x30;
  }
}


