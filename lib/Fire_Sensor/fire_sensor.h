#ifndef FIRE_SENSOR_H
#define FIRE_SENSOR_H

#define FIRE_GPIO_MASK APB_MASK_GPIO4
#define FIRE_PORT GPIO4
#define FIRE_BITS GPIO_BIT7

void FireSS_Init(void);
bool FireSS_Read(void);

#endif