#include <FlexCAN_T4.h>

#ifndef CAN_H
#define CAN_H

class NextionInterface;

class CanInterface{
public:
    CanInterface();

    static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

    static void print_can_sniff(const CAN_message_t &msg);

    static void receive_can_updates(const CAN_message_t &msg);

    static bool valid_signal();

    static void task();
};

#endif //CAN_H