#ifndef RELAY_H
#define RELAY_H

#define RELAY1_GPIO_MASK APB_MASK_GPIO4
#define RELAY2_GPIO_MASK APB_MASK_GPIO4
#define RELAY1_PORT GPIO4
#define RELAY2_PORT GPIO4
#define RELAY1_BITS GPIO_BIT0
#define RELAY2_BITS GPIO_BIT0

void Relay_Init(void);
void Relay1_ON(void);
void Relay2_ON(void);
void Relay1_OFF(void);
void Relay2_OFF(void);
void Relay1_TOGGLE(void);
void Relay2_TOGGLE(void);

#endif