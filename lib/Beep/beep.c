#include "board.h"
#include "beep.h"

void Beep_Init(void)
{
    SYS_EnableAPBClock(BEEP_GPIO_MASK);
    GPIO_SetOutput(BEEP_PORT, BEEP_BITS);
    GPIO_SetLow(BEEP_PORT, BEEP_BITS);
}

void Beep_ON(void)
{
    GPIO_SetHigh(BEEP_PORT, BEEP_BITS);
}

void Beep_OFF(void)
{
    GPIO_SetLow(BEEP_PORT, BEEP_BITS);
}

void Beep_TOGGLE(void)
{
    if (GPIO_PIN_GETVALUE(BEEP_PORT, BEEP_BITS))
    {
        GPIO_SetLow(BEEP_PORT, BEEP_BITS);
    }
    else
    {
        GPIO_SetHigh(BEEP_PORT, BEEP_BITS);
    }
}

void Beep_ON_Bits(uint8_t route_bits)
{
    GPIO_SetHigh(BEEP_PORT, route_bits);
}

void Beep_OFF_Bits(uint8_t route_bits)
{
    GPIO_SetLow(BEEP_PORT, route_bits);
}