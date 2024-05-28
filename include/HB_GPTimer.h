#ifndef HB_GPTIMER_H
#define HB_GPTIMER_H

#include "main.h"

#ifdef JUDGE_IN_WHILE
/**
 * @brief 定时器心跳结构体
 * 
 */
typedef struct HB_GPTimer
{
    uint64_t HB_Timer;
} _GPTimer_HB;
extern _GPTimer_HB HeartBeat;
#endif

void GpTimer0_Heart_Init(uint32_t arr, uint32_t psc);

#endif