#include "main.h"

uint8_t routearray[9] = {0, 0, 0, 0, 0, 0, 1, 1, 1};

void Output1_Route(bool enable1)
{
    uint8_t route_bits = routearray[0] * RELAY1_BITS | routearray[1] * RELAY2_BITS | routearray[2] * BEEP_BITS;
    GPIO_PIN_SETVALUE(DEVICE_PORT, route_bits, enable1);
}

void Output2_Route(bool enable2)
{
    uint8_t route_bits = routearray[3] * RELAY1_BITS | routearray[4] * RELAY2_BITS | routearray[5] * BEEP_BITS;
    GPIO_PIN_SETVALUE(DEVICE_PORT, route_bits, enable2);
}

void Output3_Route(bool enable3)
{
    uint8_t route_bits = routearray[6] * RELAY1_BITS | routearray[7] * RELAY2_BITS | routearray[8] * BEEP_BITS;
    GPIO_PIN_SETVALUE(DEVICE_PORT, route_bits, enable3);
}

void Device_Init(void)
{
    SYS_EnableAPBClock(DEVICE_GPIO_MASK);
    GPIO_SetOutput(DEVICE_PORT, RELAY1_BITS | RELAY2_BITS | BEEP_BITS);
}