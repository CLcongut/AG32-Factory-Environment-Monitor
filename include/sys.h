#ifndef SYS_H
#define SYS_H

#include "board.h"
#include "TASK.h"
#include "HB_GPTimer.h"
#include "DHT11.h"

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

#endif