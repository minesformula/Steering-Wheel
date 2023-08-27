#include "MailBox.h"

bool MailBox::_CANEnabled = false;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> MailBox::Can0;

MailBox::MailBox(FLEXCAN_MAILBOX MB, uint32_t ID, void (*funct)(const CAN_message_t &msg)){
    this->MB = MB;
    this->ID = ID;
    this->funct = funct;
    
    if (!(MailBox::_CANEnabled)){
        pinMode(6, OUTPUT);
        digitalWrite(6, LOW); /* optional tranceiver enable pin */
        MailBox::Can0.begin();
        MailBox::Can0.setBaudRate(1000000);
        MailBox::Can0.setMaxMB(16);
        MailBox::Can0.enableMBInterrupts();
        MailBox::Can0.setMBFilter(REJECT_ALL);
        MailBox::_CANEnabled = true;
    }

    MailBox::Can0.setMBFilter(MB, ID);
    MailBox::Can0.onReceive(funct);
}

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> MailBox::getCan(){
    return MailBox::Can0;
}