#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H
#include <vector>
#include "MailBox.h"
#include "neopixel.h"
#include "nextion.h"

class SteeringWheel{
    public:
    SteeringWheel();
    void send_shift(const bool up, const bool down);
    void update();

    private:
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

    std::vector<MailBox> mailboxes;

    bool shiftDownState;
    bool shiftUpState;
};

void process280(const CAN_message_t &msg);
void process281(const CAN_message_t &msg);
void process1280(const CAN_message_t &msg);
void process1284(const CAN_message_t &msg);

#endif