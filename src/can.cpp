#include "Arduino.h"
#include "can.h"
#include "nextion.h"
#include "neopixel.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CanInterface::Can0;

CanInterface::CanInterface(){}

bool CanInterface::canActive = false;

bool CanInterface::init(){
    pinMode(6, OUTPUT); digitalWrite(6, LOW); /* optional tranceiver enable pin */
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.setMaxMB(16);
    Can0.enableFIFO();
    Can0.enableFIFOInterrupt();
    Can0.onReceive(receive_can_updates);
    //Can0.onReceive(print_can_sniff);
    Can0.mailboxStatus();
    return 1;
}

void CanInterface::print_can_sniff(const CAN_message_t &msg){
    Serial.print("MB "); Serial.print(msg.mb);
    Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" EXT: "); Serial.print(msg.flags.extended);
    Serial.print(" TS: "); Serial.print(msg.timestamp);
    Serial.print(" ID: "); Serial.print(msg.id, DEC);
    Serial.print(" Buffer: ");
    for ( uint8_t i = 0; i < msg.len; i++ ) {
        Serial.print(msg.buf[i], DEC); Serial.print(" ");
    } 
    Serial.println();
}

void CanInterface::receive_can_updates(const CAN_message_t &msg){
    page currentPage = NextionInterface::getCurrentPage();
    canActive = true;

    if(msg.id == 280){
        if(msg.buf[0] > 2 && (currentPage != page::DRIVER))
            NextionInterface::switchToDriver();
        else if(msg.buf[0] <= 2 && (currentPage != page::STARTUP))
            NextionInterface::switchToStartUp();
    }

    switch (msg.id){
        case 280:
            NextionInterface::setRPM(msg.buf[0] * 100);
            NextionInterface::setWaterTemp(msg.buf[3]);
            RevLights::rpmBased(msg.buf[0] * 100);
            break;

        case 281:
            NextionInterface::setNeutral((msg.buf[4] & 16 ) << 0x10);
            break;

        case 1280:
            if(msg.buf[0] == 48){
                NextionInterface::setVoltage(msg.buf[2] * 0.1216);
            }
            break;

        case 1284:
            if(msg.buf[0] == 0 || msg.buf[0] == 1){
                if(msg.buf[1] == 0 || msg.buf[1] == 1){
                    NextionInterface::setWaterPumpValue(msg.buf[1]);
                    NextionInterface::setWaterPumpBool(msg.buf[1]);
                } 
                else
                    Serial.println("Water Pump Error");

                if(msg.buf[0] == 0 || msg.buf[0] == 1){
                    NextionInterface::setFuelPumpValue(msg.buf[0]);
                    NextionInterface::setFuelPumpBool(msg.buf[0]);
                }   
                else
                    Serial.println("Fuel Pump Error");

                if(msg.buf[3] == 0 || msg.buf[3] == 1){
                    NextionInterface::setFanValue(msg.buf[3]);
                    NextionInterface::setFanBool(msg.buf[3]);
                }
                else
                    Serial.println("Fan Error");
            }
        break;
        
        default:
            break;
    }
}

void CanInterface::send_shift(const bool up, const bool down){
    CAN_message_t msg;
    msg.id = 0x7DA;
    msg.buf[0] = up;
    msg.buf[1] = down;
    Can0.write(msg);
}

void CanInterface::task(){
    Can0.events();
}