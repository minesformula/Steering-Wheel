#ifndef MAILBOX_H
#define MAILBOX_H

#include <FlexCAN_T4.h>


class MailBox {
    public:
    MailBox(FLEXCAN_MAILBOX MB, uint32_t ID, void (*funct)(const CAN_message_t &msg));

    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> getCan();

    private:
    void (*funct)(const CAN_message_t &msg);
    
    FLEXCAN_MAILBOX MB;
    uint32_t ID;

    protected:
    static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
    static bool _CANEnabled;
};

#endif