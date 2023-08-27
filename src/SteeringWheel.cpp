#include "SteeringWheel.h"

const int shiftUp = 2;
const int shiftDown = 3;

SteeringWheel::SteeringWheel(){
    pinMode(shiftUp, INPUT_PULLUP); //ShiftIn
    pinMode(shiftDown, INPUT_PULLUP); //ShiftDown

    shiftUpState = false;
    shiftDownState = false;

    RevLights lights{};

    delay(400);
    Serial.begin(115200);

    NextionInterface::init();

    mailboxes.push_back(MailBox(MB0, 280, process280));
    mailboxes.push_back(MailBox(MB1, 281, process281));
    mailboxes.push_back(MailBox(MB2, 1280, process1280));
    mailboxes.push_back(MailBox(MB3, 1284, process1284));

    Can0 = mailboxes[0].getCan();
}

void SteeringWheel::send_shift(const bool up, const bool down){
    CAN_message_t msg;
    msg.id = 0x7DA;
    msg.buf[0] = up;
    msg.buf[1] = down;
    Can0.write(msg);
}

void SteeringWheel::update(){
    Can0.events();


    
    if (digitalRead(shiftUp) == 0 && shiftUpState == false)
    {
        Serial.println("Shift Up");
        send_shift(true, false);
        shiftUpState = true;
    }
    else if (digitalRead(shiftDown) == 0 && shiftDownState == false)
    {
        Serial.println("Shift Down");
        send_shift(false, true);
        shiftDownState = true;
    }
    else if (digitalRead(shiftDown) == 1 && shiftDownState == true)
    {
        send_shift(false, false);
        shiftDownState = false;
    }
    else if (digitalRead(shiftUp) == 1 && shiftUpState == true)
    {
        send_shift(false, false);
        shiftUpState = false;
    }
}


void process280(const CAN_message_t &msg){
    if (msg.buf[0] > 2 && (NextionInterface::getCurrentPage() != page::DRIVER))
        NextionInterface::switchToDriver();
    else if (msg.buf[0] <= 2 && (NextionInterface::getCurrentPage() != page::STARTUP))
        NextionInterface::switchToStartUp();

    NextionInterface::setRPM(msg.buf[0] * 100);
    NextionInterface::setWaterTemp(msg.buf[3]);
    RevLights::rpmBased(msg.buf[0] * 100);
}

void process281(const CAN_message_t &msg){
    NextionInterface::setNeutral((msg.buf[4] & 16) << 0x10);
}

void process1280(const CAN_message_t &msg){
    NextionInterface::setVoltage(msg.buf[2] * 0.1216);
}

void process1284(const CAN_message_t &msg){
    if (msg.buf[0] == 0 || msg.buf[0] == 1){
        if (msg.buf[1] == 0 || msg.buf[1] == 1)
        {
            NextionInterface::setWaterPumpValue(msg.buf[1]);
            NextionInterface::setWaterPumpBool(msg.buf[1]);
        }
        else
            Serial.println("Water Pump Error");

        if (msg.buf[0] == 0 || msg.buf[0] == 1)
        {
            NextionInterface::setFuelPumpValue(msg.buf[0]);
            NextionInterface::setFuelPumpBool(msg.buf[0]);
        }
        else
            Serial.println("Fuel Pump Error");

        if (msg.buf[3] == 0 || msg.buf[3] == 1)
        {
            NextionInterface::setFanValue(msg.buf[3]);
            NextionInterface::setFanBool(msg.buf[3]);
        }
        else
            Serial.println("Fan Error");
    }
}