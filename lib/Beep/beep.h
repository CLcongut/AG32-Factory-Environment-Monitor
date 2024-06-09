#ifndef BEEP_H
#define BEEP_H

#define BEEP_GPIO_MASK APB_MASK_GPIO4
#define BEEP_PORT GPIO4
#define BEEP_BITS GPIO_BIT0

void Beep_Init(void);
void Beep_ON(void);
void Beep_OFF(void);
void Beep_TOGGLE(void);

#endif