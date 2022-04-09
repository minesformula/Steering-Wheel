#include <Arduino.h>
#include <nextion.h>
#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

void canSniff(const CAN_message_t &msg) {
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, DEC);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], DEC); Serial.print(" ");
  } Serial.println();

  switch (msg.id)
  {
    case 281:
      setWaterTemp(msg.buf[3], true);
      Serial.println("Updated Temp");
      break;
    
    default:
    Serial.println("Hello");
      break;
    }
}

void setup(void) {
  Serial.begin(115200); delay(400);
  Serial1.begin(115200);
  delay(2000);
  switchToStartUp();
  delay(500);
  Serial.println("Nextion Setup");

  
  pinMode(6, OUTPUT); digitalWrite(6, LOW); /* optional tranceiver enable pin */
  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  Can0.mailboxStatus();
}



void loop() {
  Can0.events();

  static uint32_t timeout = millis();
  if ( millis() - timeout > 200 ) {
    CAN_message_t msg;
    msg.id = random(0x1,0x7FE);
    for ( uint8_t i = 0; i < 8; i++ ) msg.buf[i] = i + 1;
    Can0.write(msg);
    timeout = millis();

    setOilTemp(random()%210);
    setVoltage(random()%4 + 10);
  }

}