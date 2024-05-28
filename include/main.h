#ifndef MAIN_H
#define MAIN_H

/*是否使用主循环判断间隔时间，关闭则为每次定时器中断时判断*/
#define JUDGE_IN_WHILE

#include "board.h"
#include "main.h"

#include "task.h"
#include "gui.h"
#include "HB_GPTimer.h"

#include "lcd.h"
#include "lcd_init.h"
#include "DHT11.h"
#include "mq135_air_sensor.h"
#include "mq2_fumes_sensor.h"

#define MIN_IRQ_PRIORITY 1
#define MAX_IRQ_PRIORITY PLIC_MAX_PRIORITY

#define I2C_PRIORITY (MIN_IRQ_PRIORITY + 1)
#define TIMER_PRIORITY (MIN_IRQ_PRIORITY + 2)
#define DMAC_PRIORITY (MIN_IRQ_PRIORITY + 8)
#define UART_PRIORITY (MIN_IRQ_PRIORITY + 9)
#define CAN_PRIORITY (MIN_IRQ_PRIORITY + 7)
#define RTC_PRIORITY (MIN_IRQ_PRIORITY + 6)
#define EXT_PRIORITY (MIN_IRQ_PRIORITY + 4)
#define SPI_PRIORITY (MIN_IRQ_PRIORITY + 5)
#define MEMSPI_PRIORITY (MIN_IRQ_PRIORITY + 1)
#define GPIO_PRIORITY (MIN_IRQ_PRIORITY + 1)
#define FLASH_PRIORITY (MAX_IRQ_PRIORITY - 5)
#define USB_PRIORITY (MAX_IRQ_PRIORITY - 1)
#define MAC_PRIORITY (MAX_IRQ_PRIORITY - 1)
#define WDOG_PRIORITY (MAX_IRQ_PRIORITY - 0)

void _sys_Init(void);
void _sys_Load(void);
void _sys_Loop(void);

#endif