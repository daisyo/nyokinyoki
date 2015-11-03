#include <XBee.h>
#include <Servo.h>


XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();

uint8_t a;
uint8_t b;
uint8_t c;
uint8_t data[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t k;

int d = 10;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);

  servo1.attach(13);
  servo2.attach(12);
  servo3.attach(11);
  servo4.attach(10);
  servo5.attach(9);
  servo6.attach(8);
  servo7.attach(7);
  servo8.attach(6);
  servo9.attach(5);

  xbee.setSerial(Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buf[16];
  int b[9];

  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);
      strncpy(buf, (char *)zbRx.getData(), sizeof(buf));
      //Serial.println(buf);
    }

    for (int i = 0; i < 9; ++i) {
      Serial.print(buf[i]);
      b[i] = charToInt(buf[i]);
    }
    Serial.println("");
    servo1.write(b[0] * (180 / 5));
    delay(d);
    servo2.write(b[1] * (180 / 5));
    delay(d);
    servo3.write(b[2] * (180 / 5));
    delay(d);
    servo4.write(b[3] * (180 / 5));
    delay(d);
    servo5.write(b[4] * (180 / 5));
    delay(d);
    servo6.write(b[5] * (180 / 5));
    delay(d);
    servo7.write(b[6] * (180 / 5));
    delay(d);
    servo8.write(b[7] * (180 / 5));
    delay(d);
    servo9.write(b[8] * (180 / 5));
    delay(d);
  }
}  

int charToInt(char r) {
  switch (r) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    default: return 0;
  }
}

