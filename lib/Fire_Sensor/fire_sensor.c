#include "board.h"
#include "fire_sensor.h"

void FireSS_Init(void)
{
    SYS_EnableAPBClock(FIRE_GPIO_MASK);
    GPIO_SetInput(FIRE_PORT, FIRE_BITS);
}

bool FireSS_Read(void)
{
    return !GPIO_PIN_GETVALUE(FIRE_PORT, FIRE_BITS);
}
