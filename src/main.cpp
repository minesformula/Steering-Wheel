#include <Arduino.h>
#include <nextion.h>
#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

bool car_on = false;

void canSniff(const CAN_message_t &msg) {
  // Serial.print("MB "); Serial.print(msg.mb);
  // Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  // Serial.print("  LEN: "); Serial.print(msg.len);
  // Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  // Serial.print(" TS: "); Serial.print(msg.timestamp);
  // Serial.print(" ID: "); Serial.print(msg.id, DEC);
  // Serial.print(" Buffer: ");
  // for ( uint8_t i = 0; i < msg.len; i++ ) {
  //   Serial.print(msg.buf[i], DEC); Serial.print(" ");
  // } Serial.println();

  switch (msg.id)
  {
    case 280:
      setWaterTemp(msg.buf[3], true);
      break;

    case 281:
      setNeutral((msg.buf[4] & 16 ) << 0x10);
      break;

    case 1280:
      if(msg.buf[0] == 48){
        setVoltage(msg.buf[2] * 0.1216);
      }
      break;

    case 1284:
        Serial.print(msg.buf[1]);
        Serial.print(msg.buf[2]);
        Serial.print(msg.buf[3]);
        Serial.print(msg.buf[4]);
        Serial.print(msg.buf[5]);
        Serial.print(msg.buf[6]);
        Serial.println(msg.buf[7]);
      if(msg.buf[0] == 0){
        if(msg.buf[1] == 0 || msg.buf[1] == 1)
          setWaterPumpValue(msg.buf[1]);
        else
          Serial.println("Water Pump Error");

        if(msg.buf[2] == 0 || msg.buf[2] == 1){}
          //setFuelPumpValue(msg.buf[2]);
        else
          Serial.println("Fuel Pump Error");

        if(msg.buf[3] == 0 || msg.buf[3] == 1)
          setFanValue(msg.buf[3]);
        else
          Serial.println("Fan Error");
      }
      
      break;
    
    default:
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
  }

}