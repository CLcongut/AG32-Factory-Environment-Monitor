#ifndef BEEP_H
#define BEEP_H

#define BEEP_GPIO_MASK APB_MASK_GPIO4
#define BEEP_PORT GPIO4
#define BEEP_BITS GPIO_BIT0

void Beep_Init(void);
void Beep_ON(void);
void Beep_OFF(void);
void Beep_TOGGLE(void);
void Beep_ON_Bits(uint8_t route_bits);
void Beep_OFF_Bits(uint8_t route_bits);

#endif