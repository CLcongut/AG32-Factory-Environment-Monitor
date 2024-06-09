#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#define Motor_GPIO_MASK APB_MASK_GPIO4
#define Motor_GPIO_PORT GPIO4

#define Motor_A_Bit GPIO_BIT0
#define Motor_B_Bit GPIO_BIT1
#define Motor_C_Bit GPIO_BIT2
#define Motor_D_Bit GPIO_BIT3

#define MOTOR_A_H GPIO_SetHigh(Motor_GPIO_PORT, Motor_A_Bit)
#define MOTOR_A_L GPIO_SetLow(Motor_GPIO_PORT, Motor_A_Bit)

#define MOTOR_B_H GPIO_SetHigh(Motor_GPIO_PORT, Motor_B_Bit)
#define MOTOR_B_L GPIO_SetLow(Motor_GPIO_PORT, Motor_B_Bit)

#define MOTOR_C_H GPIO_SetHigh(Motor_GPIO_PORT, Motor_C_Bit)
#define MOTOR_C_L GPIO_SetLow(Motor_GPIO_PORT, Motor_C_Bit)

#define MOTOR_D_H GPIO_SetHigh(Motor_GPIO_PORT, Motor_D_Bit)
#define MOTOR_D_L GPIO_SetLow(Motor_GPIO_PORT, Motor_D_Bit)

void Motor_Init(void);                                 // 步进电机初始化
void Motor_Stop(void);                                 // 步进电机停止函数
void Motor_Control(uint8_t direction, uint32_t speed); // 步进电机转向控制函数
void Motor_Just_Angle(uint16_t angle, uint32_t speed); // 步进电机正转角度函数
void Motor_Back_Angle(uint16_t angle, uint32_t speed); // 步进电机反转角度函数
void Motor_Just_Circle(uint8_t ring, uint32_t speed);  // 步进电机正转圈函数
void Motor_Back_Circle(uint8_t ring, uint32_t speed);  // 步进电机反转圈函数

#endif