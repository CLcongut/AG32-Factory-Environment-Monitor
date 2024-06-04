#include "board.h"
#include "beep.h"

#define BEEP_GPIO_MASK APB_MASK_GPIO4
#define BEEP_PORT GPIO4
#define BEEP_BITS GPIO_BIT0

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