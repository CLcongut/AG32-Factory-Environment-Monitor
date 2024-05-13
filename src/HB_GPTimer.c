#include "SYS.h"
#include "HB_GPTimer.h"

_GPTimer_HB HeartBeat;

/**
 * @brief 通用定时器0中断返回函数
 * 
 */
void GPTIMER0_isr(void)
{
    GPTIMER_ClearFlagUpdate(GPTIMER0);
    GPTIMER_EnableCounter(GPTIMER0);
    HeartBeat.G_HB_Timer++;
}

/**
 * @brief 启用通用定时器0作为任务轮询心跳，1ms
 * 
 */
void GpTimer0_Heart_Init(void)
{
    SYS_EnableAPBClock(APB_MASK_GPTIMER0);
    GPTIMER_InitTypeDef hb_init;
    GPTIMER_StructInit(&hb_init);
    hb_init.Autoreload = 1000;
    hb_init.Prescaler = 100;
    GPTIMER_Init(GPTIMER0, &hb_init);
    GPTIMER_SetOnePulseMode(GPTIMER0, GPTIMER_ONEPULSEMODE_SINGLE);
    GPTIMER_EnableCounter(GPTIMER0);

    INT_EnableIRQ(GPTIMER0_IRQn, TIMER_PRIORITY);
    GPTIMER_EnableIntUpdate(GPTIMER0);

    HeartBeat.G_HB_Timer = 0;
}