#include "board.h"
#include "fire_sensor.h"

#define FIRE_GPIO_MASK APB_MASK_GPIO4
#define FIRE_PORT GPIO4
#define FIRE_BITS GPIO_BIT7

void FireSS_Init(void)
{
    SYS_EnableAPBClock(FIRE_GPIO_MASK);
    GPIO_SetInput(FIRE_PORT, FIRE_BITS);
}

bool FireSS_Read(void)
{
    return !GPIO_PIN_GETVALUE(FIRE_PORT, FIRE_BITS);
}
