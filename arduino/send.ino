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
    default: return 0x30;
  }
}

