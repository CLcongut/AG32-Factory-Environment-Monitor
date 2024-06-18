#ifndef ROUTE_H
#define ROUTE_H

#define DEVICE_GPIO_MASK APB_MASK_GPIO1
#define DEVICE_PORT GPIO1
#define RELAY1_BITS GPIO_BIT1
#define RELAY2_BITS GPIO_BIT2
#define BEEP_BITS GPIO_BIT0

void Output1_Route(bool enable1);
void Output2_Route(bool enable2);
void Output3_Route(bool enable3);
void Device_Init(void);

#endif