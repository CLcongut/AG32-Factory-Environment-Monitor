#include "main.h"
#include "key.h"

uint8_t Key_Code_Past;

#ifdef KEY_INT
uint8_t Key_Code_Now;
void GPIO2_isr(void)
{

    if (GPIO_IsRawIntActive(Key_PORT, Key1_BITS))
    {
        GPIO_ClearInt(Key_PORT, Key1_BITS);
        if (!Key_Code_Now)
        {
            Key_Code_Now = 1;
            Key_Code_Past = 0;
        }
    }
}
#endif

void Key_Init(void)
{
    SYS_EnableAPBClock(Key_GPIO_MASK);
    GPIO_SetInput(Key_PORT, Key1_BITS | Key2_BITS | Key3_BITS | Key4_BITS);
#ifdef KEY_INT
    GPIO_EnableInt(Key_PORT, Key1_BITS | Key2_BITS | Key3_BITS | Key4_BITS);
    GPIO_IntConfig(Key_PORT, Key1_BITS | Key2_BITS | Key3_BITS | Key4_BITS, GPIO_INTMODE_FALLEDGE);
    INT_EnableIRQ(GPIO2_IRQn, GPIO_PRIORITY);
#endif
}

#ifndef KEY_INT
uint8_t Key_Scan(void)
{
    // UART_Send(UART1, Key_PORT->GpioDATA, 16);
    uint8_t Key_Code_Raw = Key_PORT->GpioDATA[Key1_BITS | Key2_BITS | Key3_BITS | Key4_BITS];
    if (Key_Code_Raw != 0x0F)
    {
        uint8_t Key_Code;
        UART_SendCh(UART1, Key_Code_Raw);
        switch (Key_Code_Raw)
        {
        case 0x0E:
            Key_Code = 1;
            break;

        case 0x0D:
            Key_Code = 2;
            break;

        case 0x0B:
            Key_Code = 3;
            break;

        case 0x07:
            Key_Code = 4;
            break;
        }
#ifdef FALLING_TRAG
        if (Key_Code != Key_Code_Past && !Key_Code_Past)
        {
            Key_Code_Past = Key_Code;
            return Key_Code;
        }
        else
        {
            return 0;
        }
#endif
#ifdef RISING__TRAG
        if (Key_Code != Key_Code_Past && !Key_Code_Past)
        {
            Key_Code_Past = Key_Code;
            return 0;
        }
        else
        {
            return 0;
        }
#endif
    }
#ifdef FALLING_TRAG
    Key_Code_Past = 0;
#endif
#ifdef RISING__TRAG
    uint8_t Key_Code_Temp = Key_Code_Past;
    Key_Code_Past = 0;
    return Key_Code_Temp;
#endif
}
#elif defined KEY_INT
uint8_t Key_Scan(void)
{
    if (!Key_Code_Past)
    {
        Key_Code_Past = Key_Code_Now;
        Key_Code_Now = 0;
        return Key_Code_Past;
    }
    else
    {
        return 0;
    }
}
#endif