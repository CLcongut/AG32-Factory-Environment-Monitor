#ifndef KEY_H
#define KEY_H

/*切换按钮上升沿触发或者下降沿触发，只能打开一个*/
#define RISING__TRAG
// #define FALLING_TRAG
// #define KEY_INT

#define Key_GPIO_MASK APB_MASK_GPIO2
#define Key_PORT GPIO2
#define Key1_BITS GPIO_BIT0
#define Key2_BITS GPIO_BIT1
#define Key3_BITS GPIO_BIT2
#define Key4_BITS GPIO_BIT3

void Key_Init(void);
uint8_t Key_Scan(void);

#endif