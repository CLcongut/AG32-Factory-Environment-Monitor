#include "board.h"
#include "relay.h"

void Relay_Init(void)
{
    SYS_EnableAPBClock(RELAY1_GPIO_MASK);
    SYS_EnableAPBClock(RELAY2_GPIO_MASK);
    GPIO_SetOutput(RELAY1_PORT, RELAY1_BITS);
    GPIO_SetOutput(RELAY2_PORT, RELAY2_BITS);
    GPIO_SetLow(RELAY1_PORT, RELAY1_BITS);
    GPIO_SetLow(RELAY2_PORT, RELAY2_BITS);
}

void Relay1_ON(void)
{
    GPIO_SetHigh(RELAY1_PORT, RELAY1_BITS);
}

void Relay2_ON(void)
{
    GPIO_SetHigh(RELAY2_PORT, RELAY2_BITS);
}

void Relay1_OFF(void)
{
    GPIO_SetLow(RELAY1_PORT, RELAY1_BITS);
}

void Relay2_OFF(void)
{
    GPIO_SetLow(RELAY2_PORT, RELAY2_BITS);
}

void Relay1_TOGGLE(void)
{
    if (GPIO_PIN_GETVALUE(RELAY1_PORT, RELAY1_BITS))
    {
        GPIO_SetLow(RELAY1_PORT, RELAY1_BITS);
    }
    else
    {
        GPIO_SetHigh(RELAY1_PORT, RELAY1_BITS);
    }
}

void Relay2_TOGGLE(void)
{
    if (GPIO_PIN_GETVALUE(RELAY2_PORT, RELAY2_BITS))
    {
        GPIO_SetLow(RELAY2_PORT, RELAY2_BITS);
    }
    else
    {
        GPIO_SetHigh(RELAY2_PORT, RELAY2_BITS);
    }
}