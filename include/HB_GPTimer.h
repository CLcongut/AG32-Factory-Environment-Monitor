#ifndef HB_GPTIMER_H
#define HB_GPTIMER_H

#include "board.h"

/**
 * @brief 定时器心跳结构体
 * 
 */
typedef struct 
{
    uint64_t G_HB_Timer;
} _GPTimer_HB;

_GPTimer_HB HeartBeat;

#endif